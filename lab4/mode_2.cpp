#include "mode_2.h"
#include "intersept.h"
#include "mode_malfunction.h"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define T_BETWEEN_INTER 6
#define TOLERANCE 1

mode_2::mode_2(intersept* interseption):
  intersept_mode(interseption),
  _duty_cycle(0.5),
  _cars_s(0),
  _cars_w(0),
  _increments(0) { 
  i2c_post_office::get_instance().init_post_office(interseption->get_address());
}


/*===================================================================
| operate:
|   * params none
|   * returns nothing
|
| This fucntion will run on the main loop of the program and it is 
| reponsible for implementing the behavior associated with
| mode_2
===================================================================*/
void mode_2::operate() {
  /* Check for cars passing by (button presses) */
  get_intersept()->get_s_counter()->check_inc();
  get_intersept()->get_w_counter()->check_inc();

  /* If there are messages, read one and do adjustments */
  if(i2c_post_office::get_instance().has_messages()) {
    message* msg = i2c_post_office::get_instance().get_latest();
    msg->print();
    adjust_phase(msg);
    delete msg;
  }

  /* Yellow light on */
  if(get_yellow()){
    /* It is time to go green/red */
    if(get_yellow_interval()->passed()) {
      set_s_green(!get_s_green());
      set_yellow(false);
      set_main_interval(new interval(compute_right_time()+_increments));
      _increments = 0;
      delete get_yellow_interval();
      /* Starting a new cycle */
      if(get_s_green()) {
        get_intersept()->get_light_s()->gre_on();
        get_intersept()->get_light_w()->red_on();
      }
      /* Going into the 2nd part of the current cycle */
      else {
        get_intersept()->get_light_s()->red_on();
        get_intersept()->get_light_w()->gre_on();
      }
      build_send_message();
    }
  }
  /* Yellow light off */
  else {
    /* It is time to go yellow */
    if(get_main_interval()->passed()) {
      get_intersept()->get_light_s()->yel_on();
      get_intersept()->get_light_w()->yel_on();
      set_yellow(true);
      set_yellow_interval(new interval(UNIT));
      delete get_main_interval(); 
    }

    /* 
    | Detection of broken led. If the led
    | is broke, then we change the functioning
    | mode off the interception
    */
    if(get_s_green()) {
      if(get_intersept()->get_light_w()->red_broke())
        get_intersept()->set_mode(
          new mode_malfunction(get_intersept(), this, false)
        );
    }
    else {
      if(get_intersept()->get_light_s()->red_broke())
        get_intersept()->set_mode(
          new mode_malfunction(get_intersept(), this, true)
        );
    }
  }
}

/*===================================================================
| compute_right_time:
|   * params none
|   * returns:
|     * the time interval that the next green or red light should be
|       on
|
| This will run every period, essecially, if we are going to phase
| zero (begin of a cycle) it computes the new duty_cycle and returns
| the total period times that, otherwise it will return 1-duty_cycle
| times the period
===================================================================*/
int mode_2::compute_right_time() {
  float res = 0.0;

  if(get_s_green()) {
    int cars_s = get_intersept()->get_s_counter()->get_count();
    int cars_w = get_intersept()->get_w_counter()->get_count();
    if(cars_s==0 && cars_w==0){
      _duty_cycle = 0.5;
      return 0.5*PERIOD*UNIT;
    }
    res = _duty_cycle = cars_s / (cars_s + cars_w);
  }
  else {
    res = 1 - _duty_cycle;
  } 

  res = res > 0.75 ? 0.75 : res;
  res = res < 0.25 ? 0.25 : res;

  _duty_cycle = _duty_cycle > 0.75 ? 0.75 : _duty_cycle;
  _duty_cycle = _duty_cycle < 0.25 ? 0.25 : _duty_cycle;

  return res*PERIOD*UNIT;
}

/*===================================================================
| build_send_message:
|   * params none
|   * returns nothing
|
| This function just builds a message based on the state of
| our interception and the sends the message to the
| i2c_post_office
===================================================================*/
void mode_2::build_send_message() {
  for(int i=0; i<4; i++){
    byte source = get_intersept()->get_address();
    byte destination = get_intersept()->get_neigh_addrs()[i];
    byte event = 0;
    if(get_s_green())
      event = (byte) get_intersept()->get_s() ? 1 : 0;
    else 
      event = (byte) get_intersept()->get_w() ? 3 : 2;
    byte cars_N = (byte) get_intersept()->get_s() ? 0 : get_intersept()->get_s_counter()->get_count() - _cars_s;
    byte cars_S = (byte) get_intersept()->get_s() ? get_intersept()->get_s_counter()->get_count() - _cars_s : 0;
    byte cars_E = (byte) get_intersept()->get_w() ? 0 : get_intersept()->get_w_counter()->get_count() - _cars_w;
    byte cars_W = (byte) get_intersept()->get_w() ? get_intersept()->get_w_counter()->get_count() - _cars_w : 0;
    
    message to_send(destination, source, event, cars_N, cars_S, cars_E, cars_W);
    i2c_post_office::get_instance().send_message(&to_send);
  }

  /*
  | The code bellow makes sure that, in each message we send
  | only information regarding the last control period,
  | not the whole period (whole 20 seconds)
  | If the green light on the south is supposed to be on
  | then we started a new cycle so we should reset the counters
  */
  if(get_s_green()) {
    get_intersept()->get_s_counter()->reset();
    get_intersept()->get_w_counter()->reset();
    _cars_s = 0;
    _cars_w = 0;
  }
  else{
    _cars_s = get_intersept()->get_s_counter()->get_count();
    _cars_w = get_intersept()->get_w_counter()->get_count();
  }
}


/*===================================================================
| adjust_phase:
|   * params:
|     * msg -> message in which we will base our decision of phase
|     adjustment
|   * returns nothing
| 
| This function will try to adjust the phase of our controller
| based on information from other controllers. First we extract
| information about the other controller (from the message).
| Then, based on that information we see if it is even a controller
| with which we should try to adjust phases with and finally
| we come up with our decision: if we shoulf increase our period,
| decresease it, or keep it unchanged.
===================================================================*/
void mode_2::adjust_phase(message* msg) {
  /*
  | Determine direction of maximum traffic
  | in our controller
  */
  int our_dir = -1;
  if(get_intersept()->get_s_counter()>get_intersept()->get_w_counter())
    our_dir = get_intersept()->get_s() ? SOUTH : NORTH;
  else
    our_dir = get_intersept()->get_w() ? WEST : EAST;
  
  int oth_x = (int) (msg->get_source()>>4);
  Serial.print("Other x-> ");
  Serial.println(oth_x);
  int oth_y = (int) (msg->get_source()&15);
  Serial.print("Other y-> ");
  Serial.println(oth_y);
  int oth_cars_N = (int) msg->get_cars_N();
  int oth_cars_S = (int) msg->get_cars_S();
  int oth_cars_E = (int) msg->get_cars_E();
  int oth_cars_W = (int) msg->get_cars_W();

  int max_cars = max(oth_cars_N, oth_cars_S);
  max_cars = max(max_cars, oth_cars_E);
  max_cars = max(max_cars, oth_cars_W);

  if(max_cars==0){
    Serial.println("Return cause zero");
    return;
  }

  /*
  | Determine direction of maximum traffic 
  | on the other controller
  */
  int oth_dir = -1;
  if(max_cars==oth_cars_N)
    oth_dir = NORTH;
  else if(max_cars==oth_cars_S)
    oth_dir = SOUTH;
  else if(max_cars==oth_cars_E)
    oth_dir = EAST;
  else if(max_cars==oth_cars_W) 
    oth_dir = WEST;
  
  /*
  | Is the maximum traffic from both controllers
  | coming from the same direction?
  | If some, keep in going
  | Return otherwise
  */
  if(our_dir!=oth_dir) {
    Serial.println("Return cause diff directions");
    return;
  }

  Serial.print("Other direction-> ");
  Serial.println(oth_dir);

  Serial.print("Our direction-> ");
  Serial.println(our_dir);

  /*
  | Orietation is fine, but we still need to check
  | our interceptions are placed relative to each other
  */
  if(our_dir==NORTH) {
    if(get_intersept()->get_y()>oth_y) return;
  }
  else if(our_dir==SOUTH) {
    if(get_intersept()->get_y()<oth_y) return;
  }
  else if(our_dir==EAST) {
    if(get_intersept()->get_x()>oth_x) return;
  }
  else if(our_dir==WEST) {
    if(get_intersept()->get_x()<oth_x) return;
  }

  int our_phase = -1;
  if(get_yellow()) {
    our_phase = get_s_green() ? 0 : _duty_cycle*PERIOD;
  }
  else {
    float percent_curr_cycle = ((double) get_main_interval()->get_passed())/(double)get_main_interval()->get_interval();
    Serial.print("Percentage ->");
    Serial.println(percent_curr_cycle);
    Serial.println(get_main_interval()->get_passed());
    Serial.println(get_main_interval()->get_interval());
    Serial.println(_duty_cycle);
    if(get_s_green())
      our_phase = percent_curr_cycle*_duty_cycle*PERIOD;
    else
      our_phase = _duty_cycle*PERIOD + percent_curr_cycle*(1-_duty_cycle)*PERIOD;
  }

  int event = (int) msg->get_event();
  int oth_phase = -1;
  float oth_duty_cycle = oth_cars_S + oth_cars_N / (oth_cars_S + oth_cars_N + oth_cars_E + oth_cars_W);

  oth_duty_cycle = oth_duty_cycle > 0.75 ? 0.75 : oth_duty_cycle;
  oth_duty_cycle = oth_duty_cycle < 0.25 ? 0.25 : oth_duty_cycle;

  if(event==0||event==1)
    oth_phase = 0;
  else
    oth_phase = oth_duty_cycle*PERIOD;

  Serial.print("Other phase-> ");
  Serial.println(oth_phase);

  Serial.print("Our phase-> ");
  Serial.println(our_phase);

  if(oth_phase<our_phase)
    oth_phase+=20;
  int diff = oth_phase-our_phase;
  if(diff+TOLERANCE==T_BETWEEN_INTER ||
     diff-TOLERANCE==T_BETWEEN_INTER ||
     diff==T_BETWEEN_INTER){
    Serial.println("Return cause alreaddy alligned");
    return;
  }

  if(diff>T_BETWEEN_INTER) {
    _increments = -1*UNIT;
    Serial.println("Decreasing");
  }
  else {
    _increments = 1*UNIT; 
    Serial.println("Increasing");
  }
}

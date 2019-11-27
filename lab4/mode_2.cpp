#include "mode_2.h"
#include "intersept.h"
#include "mode_malfunction.h"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define T_BETWEEN_INTER 6

mode_2::mode_2(intersept* interseption):
  intersept_mode(interseption),
  _duty_cycle(0.5),
  _cars_s(0),
  _cars_w(0),
  _increments(0) { 
  i2c_post_office::get_instance().init_post_office(interseption->get_address());
}

void mode_2::operate() {
  get_intersept()->get_s_counter()->check_inc();
  get_intersept()->get_w_counter()->check_inc();
  if(i2c_post_office::get_instance().has_messages()) {
    message* msg = i2c_post_office::get_instance().get_latest();
    msg->print();
    adjust_phase(msg);
    delete msg;
  }

  if(get_yellow()){
    if(get_yellow_interval()->passed()) {
      set_s_green(!get_s_green());
      set_yellow(false);
      set_main_interval(new interval(compute_right_time()+_increments));
      _increments = 0;
      delete get_yellow_interval();
      if(get_s_green()) {
        get_intersept()->get_light_s()->gre_on();
        get_intersept()->get_light_w()->red_on();
      }
      else {
        get_intersept()->get_light_s()->red_on();
        get_intersept()->get_light_w()->gre_on();
      }
      build_send_message();
    }
  }
  else {
    if(get_main_interval()->passed()) {
      get_intersept()->get_light_s()->yel_on();
      get_intersept()->get_light_w()->yel_on();
      set_yellow(true);
      set_yellow_interval(new interval(UNIT));
      delete get_main_interval(); 
    }

    /*Detection of broken led*/
    if(get_s_green())
      if(get_intersept()->get_light_w()->red_broke())
        get_intersept()->set_mode(
          new mode_malfunction(get_intersept(), this, false)
        );
    else
      if(get_intersept()->get_light_s()->red_broke())
        get_intersept()->set_mode(
          new mode_malfunction(get_intersept(), this, true)
        );
  }
}

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

void mode_2::adjust_phase(message* msg) {
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

  int oth_dir = -1;
  if(max_cars==oth_cars_N)
    oth_dir = NORTH;
  else if(max_cars==oth_cars_S)
    oth_dir = SOUTH;
  else if(max_cars==oth_cars_E)
    oth_dir = EAST;
  else if(max_cars==oth_cars_W) 
    oth_dir = WEST;
  
  if(our_dir!=oth_dir) {
    Serial.println("Return cause diff directions");
    return;
  }

  Serial.print("Other direction-> ");
  Serial.println(oth_dir);

  Serial.print("Our direction-> ");
  Serial.println(our_dir);

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
  if(diff+1==6||diff-1==6||diff==6){
    Serial.println("Return cause alreaddy alligned");
    return;
  }

  if(diff>6) {
    _increments = -1*UNIT;
    Serial.println("Decreasing");
  }
  else {
    _increments = 1*UNIT; 
    Serial.println("Increasing");
  }
}

#include "mode_2.h"
#include "intersept.h"

mode_2::mode_2(intersept* interseption):
  intersept_mode(interseption),
  _duty_cycle(0.5) { 
  i2c_post_office::get_instance().init_post_office(get_intersept()->get_address());
}

void mode_2::operate() {
  get_intersept()->get_s_counter()->check_inc();
  get_intersept()->get_w_counter()->check_inc();
  message* msg = i2c_post_office::get_instance().get_latest();
  if(msg != nullptr) {
    msg->print();
    delete msg;
    Serial.print("Stuff all the time, though");
  }

  if(get_yellow()){
    if(get_yellow_interval()->passed()) {
      set_s_green(!get_s_green());
      set_yellow(false);
      set_main_interval(new interval(compute_right_time()));
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
  }
}

int mode_2::compute_right_time() {
  float res = 0.0;

  if(get_s_green()) {
    int cars_s = get_intersept()->get_s_counter()->get_count_reset();
    int cars_w = get_intersept()->get_w_counter()->get_count_reset();
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

  return res*PERIOD*UNIT;
}

void mode_2::build_send_message() {
  for(int i=0; i<4; i++){
    byte source = get_intersept()->get_address();
    byte destination = get_intersept()->get_neigh_addrs()[i];
    byte event = 0;
    if(get_s_green())
      event = get_intersept()->get_s() ? 1 : 0;
    else 
      event = get_intersept()->get_w() ? 3 : 2;
    byte cars_N = get_intersept()->get_s() ? 0 : get_intersept()->get_s_counter()->get_count();
    byte cars_S = get_intersept()->get_s() ? get_intersept()->get_s_counter()->get_count() : 0;
    byte cars_E = get_intersept()->get_w() ? get_intersept()->get_w_counter()->get_count() : 0;
    byte cars_W = get_intersept()->get_w() ? 0 : get_intersept()->get_w_counter()->get_count();
    message* to_send = new message(destination, source, event, cars_N, cars_S, cars_E, cars_W);
    Serial.println("Here, bro");
    i2c_post_office::get_instance().send_message(to_send);
    Serial.println("Up top, bro");
    delete to_send;
  }
}

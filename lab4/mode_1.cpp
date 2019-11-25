#include "mode_1.h"
#include "intersept.h"

mode_1::mode_1(intersept* interseption):
  intersept_mode(interseption),
  _duty_cycle(0.5) { /*Do Nothing*/ }

void mode_1::operate() {
  get_intersept()->get_s_counter()->check_inc();
  get_intersept()->get_w_counter()->check_inc();
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

int mode_1::compute_right_time() {
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

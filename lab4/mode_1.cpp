#include "mode_1.h"
#include "intersept.h"
#include "mode_malfunction.h"

mode_1::mode_1(intersept* interseption):
  intersept_mode(interseption),
  _duty_cycle(0.5) { /*Do Nothing*/ }

/*===================================================================
| operate:
|   * params none
|   * returns nothing
|
| This fucntion will run on the main loop of the program and it is 
| reponsible for implementing the behavior associated with
| mode_1
===================================================================*/
void mode_1::operate() {
  /* Check for cars passing by (button presses) */
  get_intersept()->get_s_counter()->check_inc();
  get_intersept()->get_w_counter()->check_inc();

  /* Yellow light on */
  if(get_yellow()){
    /* It is time to go green/red */
    if(get_yellow_interval()->passed()) {
      set_s_green(!get_s_green());
      set_yellow(false);
      set_main_interval(new interval(compute_right_time()));
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

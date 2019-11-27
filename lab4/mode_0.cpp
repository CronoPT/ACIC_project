/* FILENAME - mode_0.cpp */

#include "mode_0.h"
#include "intersept.h"
#include "mode_malfunction.h"

mode_0::mode_0(intersept* interseption): 
  intersept_mode(interseption) { /*Do Nothing*/ }

/*===================================================================
| operate:
|   * params none
|   * returns nothing
|
| This fucntion will run on the main loop of the program and it is 
| reponsible for implementing the behavior associated with
| mode_0
===================================================================*/
void mode_0::operate() {
  /* Yellow light on */
  if(get_yellow()){
    /* It is time to go green/red */
    if(get_yellow_interval()->passed()) {
      set_s_green(!get_s_green());
      set_yellow(false);
      set_main_interval(new interval(PERIOD*UNIT/2-UNIT));
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

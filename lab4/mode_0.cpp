#include "mode_0.h"
#include "intersept.h"

mode_0::mode_0(intersept*): 
  intersept_mode(interseption) { /*Do Nothing*/ }

void mode_0::operate() {
  if(get_yellow()){
    if(get_yellow_interval()->passed()) {
      set_s_green(!get_s_green());
      set_yellow(false);
      set_main_interval(new interval(PERIOD*UNIT/2-UNIT));
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

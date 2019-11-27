#include "mode_malfunction.h"
#include "intersept.h"

mode_malfunction::mode_malfunction(intersept* interseption,
                                   intersept_mode* prev,
                                   bool broke_s): 
  intersept_mode(interseption), _prev(prev),
  _broke_s(broke_s) { /*Do Nothing*/ }

void mode_malfunction::operate() {
  /* Time to blink */
  if(get_yellow_interval()->passed()){
    if(get_yellow()){
      get_intersept()->get_light_s()->all_off();
      get_intersept()->get_light_w()->all_off();
    }
    else {
      get_intersept()->get_light_s()->yel_on();
      get_intersept()->get_light_w()->yel_on();
    }
    set_yellow(!get_yellow());
    delete get_yellow_interval();
    set_yellow_interval(new interval(UNIT));
  }

  /* Check if the led is back on, return to normal operation */
  if(!get_yellow()) {
    if(_broke_s) {
      get_intersept()->get_light_s()->red_on();
      if(!get_intersept()->get_light_s()->red_broke()) {
        get_intersept()->set_mode(_prev);
        delete this;
      }
      get_intersept()->get_light_s()->all_off();
    }
    else {
      get_intersept()->get_light_w()->red_on();
      if(!get_intersept()->get_light_w()->red_broke()){
        get_intersept()->set_mode(_prev);
        delete this;
      }
      get_intersept()->get_light_w()->all_off();
    }
  }
}

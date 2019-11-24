#ifndef __COUNTER_H__
#define __COUNTER_H__

#include "debounced_button.h"

class counter {
  int _count;
  debounced_button* _button;

  public:
  counter(int button_pin):
    _button(button_pin) { /*Don Nothing*/ }

  int get_count_reset() { 
    int count = _count;
    _count = 0;
    return count;
  }
  
};

#endif

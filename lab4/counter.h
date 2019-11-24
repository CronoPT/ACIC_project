#ifndef __COUNTER_H__
#define __COUNTER_H__

#include "debounced_button.h"

class counter {
  int _count;
  debounced_button* _button;

  public:
  counter(int button_pin):
    _count(0),
    _button(button_pin) { 
      _button = new debounced_button(button_pin);
    }

  int get_count_reset() { 
    int count = _count;
    _count = 0;
    return count;
  }

  void check_inc() {
    if(_button->pressed()) {
      _count += 1;
      Serial.print("Counts -> ");
      Serial.println(_count);
    }
  }
  
};

#endif

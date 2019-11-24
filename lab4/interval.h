#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <Arduino.h>

class interval {
  int _interval;
  unsigned long _curr_millis;
  unsigned long _prev_millis;
  unsigned long _time_gap;  

  public:
  interval(int interval):
    _interval(interval), 
    _curr_millis(0), 
    _prev_millis(0),
    _time_gap(0) { /*Do nothing*/
    _prev_millis = millis();    
  }

  void set_interval(int interval) {
    _interval = interval;
  }

  void inc_interval(int to_inc) {
    _interval += to_inc;
  }
  
  bool passed() {
    bool passed = false;
    _curr_millis = millis();
   
    if( _curr_millis-_prev_millis >= _interval) {
      _prev_millis = _curr_millis;
      passed = true;
    }
    
    return passed;
  }

  void freeze() {
    _time_gap = millis() - _prev_millis;
  }

  void unfreeze() {
    _prev_millis = millis() - _time_gap;
  }
};

#endif

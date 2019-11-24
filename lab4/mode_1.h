#ifndef __MODE_1_H__
#define __MODE_1_H__

#include "intersept_mode.h"

class mode_1: public intersept_mode {
  float _duty_cycle;

  public:
  mode_1(intersept* interseption):
    intersept_mode(interseption),
    _duty_cycle(0.5) { /*Do Nothing*/ }
    
  void operate() override ;
  int compute_right_time();
  
};

#endif

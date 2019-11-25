#ifndef __MODE_1_H__
#define __MODE_1_H__

#include "intersept_mode.h"

class mode_1: public intersept_mode {
  float _duty_cycle;

  public:
  mode_1(intersept* interseption);
  void operate() override ;
  int compute_right_time();
};

#endif

#ifndef __MODE_2_H__
#define __MODE_2_H__

#include "intersept_mode.h"
#include "message.h"
#include "i2c_post_office.h"

class mode_2: public intersept_mode {
  float _duty_cycle;
  
  public:
  mode_2(intersept* interseption);
  void operate() override ;
  message* build_message();
  int compute_right_time();
  void build_send_message();
};

#endif

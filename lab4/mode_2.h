/* FILENAME - mode_2.h */

#ifndef __MODE_2_H__
#define __MODE_2_H__

#include "intersept_mode.h"
#include "message.h"
#include "i2c_post_office.h"

class mode_2: public intersept_mode {
  /* 
  | Duty cycle on current cycle (percentage of time 
  | the green light on the south is on) 
  */
  float _duty_cycle;

  /*
  | How many cars passed in the south direction 
  | during the first part of the cycle
  */
  int _cars_s;

  /*
  | How many cars passed in the south direction 
  | during the first part of the cycle
  */
  int _cars_w;

  /*
  | How many milliseconds we should increment in the
  | next main interval (main interval meaning the time
  | in which the red and green are on in the first or second
  | half of each cycle)
  */
  int _increments;
  
  public:
  mode_2(intersept* interseption);
  void operate() override ;
  message* build_message();
  int compute_right_time();
  void build_send_message();
  void adjust_phase(message* msg);
};

#endif

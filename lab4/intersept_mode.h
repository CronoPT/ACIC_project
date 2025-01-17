/* FILENAME - intersept_mode.h */

#ifndef __INTERSEPT_MODE_H__
#define __INTERSEPT_MODE_H__

#include "interval.h"
#include "configs.h"

class intersept;

class intersept_mode {
  /*
  | The interception whose behavior the
  | mode is implementing
  */
  intersept* _intersept;

  /*
  | Interval for red/green lights
  */
  interval*  _main_interval;

  /*
  | Interval for yellow lights
  */
  interval*  _yellow_interval;

  /*
  | If the green light in the south is on
  | it is true (1st half of the cycle)
  | If the green light in the west is on
  | it is false (2nd half of the cycle)
  */
  bool _s_green;

  /*
  | If the lights are yellow it is true
  | If they are not it is false
  */
  bool _yellow;

  protected:
  intersept_mode(intersept* interseption):
    _intersept(interseption),
    _main_interval(nullptr),
    _yellow_interval(nullptr),
    _s_green(true),
    _yellow(false) { /*Do Nothing*/ }
  
  public:
  virtual void operate() = 0;

  intersept* get_intersept() const { return _intersept; }
  interval* get_main_interval() const { return _main_interval; }
  interval* get_yellow_interval() const { return _yellow_interval; }
  bool get_s_green() const { return _s_green; }
  bool get_yellow() const { return _yellow; }
  
  void set_main_interval(interval* main_interval) { _main_interval = main_interval; }
  void set_yellow_interval(interval* yellow_interval) { _yellow_interval = yellow_interval; }
  void set_s_green(bool s_green) { _s_green = s_green; }
  void set_yellow(bool yellow) { _yellow = yellow; }

};

#endif

#ifndef __INTERSEPT_H__
#define __INTERSEPT_H__

#include "intersept_mode.h"
#include "traffic_light.h"
#include "counter.h" //the button that couts the cars

#define UNIT 1000     //one second
#define INIT_GREEN 10 //half the period

#define S_RED
#define S_YEL
#define S_GRE
#define S_BUTTON

#define W_RED
#define W_YEL
#define W_GRE
#define W_BUTTON

class intersept {
  int _x;
  int _y;
  bool _s; // south?
  bool _w; // west?
  int _green_t; //period of T
  intersept_mode* _mode;
  traffic_light*  _light_s;
  traffic_light*  _light_w;
  counter* _s_counter;
  counter* _w_counter;
  
  public:
  intersept(int x, int y, bool s, bool w, int mode):
    _x(x), _y(y), _s(s), _w(w),
    _green_T(INIT_GREEN),
    _light_s(S_RED, S_YEL, S_GRE),
    _light_w(W_RED, W_YEL, W_GRE),
    _s_counter(S_BUTTON),
    _w_counter(W_BUTTON) { 

    /* probabily had initial mode for boot sequence */
    if(mode==0)
      _mode = new mode_0(this);
    else if(mode==1)
      _mode = new mode_1(this);
    else if(mode==2)
      _mode = new mode_2(this);
  }
  
  void operate() { _mode->operate(); }

  int get_x() const { return _x; }
  int get_y() const { return _y; }
  bool get_s() const { return _s; }
  bool get_w() const { return _w; }
  int get_green_t() const {return _green_t; }
  traffic_light* get_light_s() const { return _light_s; }
  traffic_light* get_light_w() const { return _light_w; }
  counter* get_counter() const { return _counter; }
  
};

#endif

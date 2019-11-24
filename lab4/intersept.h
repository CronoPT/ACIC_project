#ifndef __INTERSEPT_H__
#define __INTERSEPT_H__

#include "intersept_mode.h"
#include "traffic_light.h"
#include "counter.h" //the button that couts the cars
#include "configs.h"
#include "intersept_mode.h"
#include "mode_0.h"
#include "mode_1.h"
#include "mode_2.h"

class intersept {
  int _x;
  int _y;
  bool _s;
  bool _w;
  int _s_green_t; 
  int _w_green_t;
  intersept_mode* _mode;
  traffic_light*  _light_s;
  traffic_light*  _light_w;
  counter* _s_counter;
  counter* _w_counter;
  
  public:
  intersept(int x, int y, bool s, bool w, int mode):
    _x(x), _y(y), _s(s), _w(w),
    _s_green_t(INIT_GREEN*UNIT),
    _w_green_t(PERIOD-INIT_GREEN),
    _mode(nullptr),
    _light_s(S_RED, S_YEL, S_GRE),
    _light_w(W_RED, W_YEL, W_GRE),
    _s_counter(S_BUTTON),
    _w_counter(W_BUTTON) { 

    _light_s = new traffic_light(S_RED, S_YEL, S_GRE);
    _light_w = new traffic_light(W_RED, W_YEL, W_GRE);

    _s_counter = new counter(S_BUTTON);
    _w_counter = new counter(W_BUTTON);
    
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
  int get_s_green_t() const { return _s_green_t; }
  int get_w_green_t() const { return _w_green_t; }
  traffic_light* get_light_s() const { return _light_s; }
  traffic_light* get_light_w() const { return _light_w; }
  counter* get_s_counter() const { return _s_counter; }
  counter* get_w_counter() const { return _w_counter; }  
  
};

#endif

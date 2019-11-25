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
#include "i2c_post_office.h"

class intersept {
  int _x;
  int _y;
  bool _s;
  bool _w;
  byte _address;
  byte _neigh_addrs[4];
  int _s_green_t; 
  int _w_green_t;
  intersept_mode* _mode;
  traffic_light*  _light_s;
  traffic_light*  _light_w;
  counter* _s_counter;
  counter* _w_counter;
  
  public:
  intersept(int mode):
    _s_green_t(INIT_GREEN*UNIT),
    _w_green_t(PERIOD-INIT_GREEN),
    _light_s(new traffic_light(S_RED, S_YEL, S_GRE)),
    _light_w(new traffic_light(W_RED, W_YEL, W_GRE)),
    _s_counter(new counter(S_BUTTON)),
    _w_counter(new counter(W_BUTTON)) { 
    
    init_coordinate();
    _x = init_x();
    _y = init_y();
    _s = init_s();
    _w = init_w();
    _address = (byte) ((_x<<4) + _y);

    Serial.println(_x);
    Serial.println(_y);
    Serial.println(_s ? "South" : "North");
    Serial.println(_w ? "West" : "East");
    Serial.println(_address);

    
    _neigh_addrs[0] = (byte) (((_x-1)<<4) + _y);
    _neigh_addrs[1] = (byte) (((_x+1)<<4) + _y);
    _neigh_addrs[2] = (byte) ((_x<<4) + (_y-1));
    _neigh_addrs[3] = (byte) ((_x<<4) + (_y+1));

    for(int i=0; i<4; i++)
      Serial.println(_neigh_addrs[i]);
    
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
  byte get_address() const { return _address; }
  byte* get_neigh_addrs() const { return _neigh_addrs; }
  int get_s_green_t() const { return _s_green_t; }
  int get_w_green_t() const { return _w_green_t; }
  traffic_light* get_light_s() const { return _light_s; }
  traffic_light* get_light_w() const { return _light_w; }
  counter* get_s_counter() const { return _s_counter; }
  counter* get_w_counter() const { return _w_counter; }

  void init_coordinate() {
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(DS, INPUT);
    pinMode(DW, INPUT);
  }

  int init_x() {
    int x = (int) (analogRead(A2) > 100 ? 1 : 0);
    x = (x*2) + (int) (analogRead(A1) > 100 ? 1 : 0);
    x = (x*2) + (int) (analogRead(A0) > 100 ? 1 : 0);
    return x;
  }

  int init_y() {
    int y = (int) (digitalRead(10)==HIGH ? 1 : 0);
    y = (y*2) + (int) (digitalRead(11)==HIGH ? 1 : 0);
    y = (y*2) + (int) (digitalRead(12)==HIGH ? 1 : 0);
    return y;
  }

  bool init_s() { return digitalRead(DS)==HIGH; }

  bool init_w() { return digitalRead(DW)>100; }
  
};

#endif

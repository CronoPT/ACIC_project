/* FILENAME - intersept.h */

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

  /* Operation mode */
  intersept_mode* _mode;

  /* Traffic light in south direction */
  traffic_light*  _light_s;

  /* Traffic light in the west direction */
  traffic_light*  _light_w;

  /* Counter for cars in the south direction*/
  counter* _s_counter;

  /* Counter for cars in the south direction*/
  counter* _w_counter;
  
  public:
  intersept(int mode):
    _light_s(new traffic_light(S_RED, S_YEL, S_GRE, DETECT_PIN_S)),
    _light_w(new traffic_light(W_RED, W_YEL, W_GRE, DETECT_PIN_W)),
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
  
  /*===================================================================
  | operate:
  |   * params none
  |   * returns nothing
  | 
  | This function runs in the main loop. It is delegating the behavior
  | on the mode
  ===================================================================*/
  void operate() { _mode->operate(); }

  int get_x() const { return _x; }
  int get_y() const { return _y; }
  bool get_s() const { return _s; }
  bool get_w() const { return _w; }
  byte get_address() const { return _address; }
  byte* get_neigh_addrs() const { return _neigh_addrs; }
  traffic_light* get_light_s() const { return _light_s; }
  traffic_light* get_light_w() const { return _light_w; }
  counter* get_s_counter() const { return _s_counter; }
  counter* get_w_counter() const { return _w_counter; }

  void set_mode(intersept_mode* new_mode) { _mode = new_mode;}

  void init_coordinate() {
    pinMode(b0, INPUT);
    pinMode(b1, INPUT);
    pinMode(b2, INPUT);
    pinMode(a0, INPUT);
    pinMode(DS, INPUT);
    pinMode(DW, INPUT);
  }

  int init_x() {
    int analog_value = (int) (analogRead(a0));
    if(analog_value<50)
      return 0;
    else if(analog_value<220)
      return 1;
    else if(analog_value<350)
      return 2;
    else if(analog_value<480)
      return 3;
    else if(analog_value<600)
      return 4;
    else if(analog_value<720)
      return 5;
    else if(analog_value<840)
      return 6;
    else
      return 7;
  }

  int init_y() {
    int y = (int) (digitalRead(b2)==HIGH ? 1 : 0);
    y = (y*2) + (int) (digitalRead(b1)==HIGH ? 1 : 0);
    y = (y*2) + (int) (digitalRead(b0)==HIGH ? 1 : 0);
    return y;
  }

  bool init_s() { return digitalRead(DS)==HIGH; }

  bool init_w() { return digitalRead(DW)>100; }
  
};

#endif

#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include "led.h"

class traffic_light {
  led* _red_led;
  led* _yel_led;
  led* _gre_led;

  public:
  traffic_light(int red_pin, int yel_pin, int gre_pin):
    _red_led(red_pin),
    _yel_led(yel_pin),
    _gre_led(gre_pin) { /* Do Nothing */ Serial.println("Building traffic light"); }

  void red_on() const {
    _red_led->on();
    _yel_led->off();
    _gre_led->off();
  }
  
  void yel_on() const {
    _red_led->off();
    _yel_led->on();
    _gre_led->off();
  }
  
  void gre_on() const {
    _red_led->off();
    _yel_led->off();
    _gre_led->on();
  }    

  void all_off() const {
    _red_led->off();
    _yel_led->off();
    _gre_led->off();
  }
  
};

#endif
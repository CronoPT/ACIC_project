#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__



#include "led.h"

class traffic_light {
  led* _red_led;
  led* _yel_led;
  led* _gre_led;
  int _detection_pin;

  public:
  traffic_light(int red_pin, int yel_pin, int gre_pin, int detection_pin):
    _detection_pin(detection_pin),
    
    _red_led(_red_led = new led(red_pin)),
    _yel_led(_yel_led = new led(yel_pin)),
    _gre_led(_gre_led = new led(gre_pin)) {
    /*Do Nothing*/
  }

  bool red_broke()
  {
    int input = 0;
    if(_detection_pin == 1)
    //for(int i = 0; i<10; i++)
      input += analogRead(A4)>100 ? 1 : 0; 
    else
    //for(int i = 0; i<10; i++)
      input += analogRead(A5)>100 ? 1 : 0;
    if(input>0)
    return true;
    else false;
  }
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

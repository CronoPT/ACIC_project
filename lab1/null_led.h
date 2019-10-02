#ifndef __NULL_LED_H__
#define __NULL_LED_H__

#include "led.h"

class null_led: public led {
  public:
  null_led():led()               { /*Do nothing*/ }  
  void set_pin(int pin) override { /*Do nothing*/ }
  void on()             override { /*Do nothing*/ }
  void off()            override { /*Do nothing*/ }
};

#endif

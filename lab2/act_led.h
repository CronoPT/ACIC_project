#ifndef __ACT_LED_H__
#define __ACT_LED_H__

#include "actuator.h"

class act_led: public actuator {
  int _pin; //must be a PWM pin

  public:
  act_led(int pin): actuator(),
    _pin(pin) {
    pinMode(_pin, OUTPUT);
    analogWrite(_pin, 0);
  }
    
  void activate(int analog_read) override {
    int brightness = map(analog_read, 0, 1023, 0, 255); 
    analogWrite(_pin, brightness);
  }
  
};

#endif

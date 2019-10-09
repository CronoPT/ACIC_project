#ifndef __SEN_POTENTIOMETER_H__
#define __SEN_POTENTIOMETER_H__

#include "sensor.h"

class sen_potentiometer: public sensor {
  int _pin; //must be an analog pin

  public:
  sen_potentiometer(int pin): sensor(),
    _pin(pin) {
    pinMode(_pin, INPUT);    
  }

  int activated() override {
    return analogRead(_pin);
  }
  
};

#endif

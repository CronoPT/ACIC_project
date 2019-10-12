#ifndef __BLINKING_LED_H__
#define __BLINKING_LED_H__

#include "interval.h"

class blinking_led {
  int _pin;
  int _state;
  interval _interval;

  public:
  blinking_led(int pin, int interval):
    _pin(pin),
    _state(LOW),
    _interval(interval) {
    pinMode(_pin, OUTPUT);
    analogWrite(_pin, 0);
  }
    
  void set_interval(int interval) {
    _interval.set_interval(interval);
    if( _interval.passed() )
      digitalWrite(_pin, ( _state = _state==LOW ? HIGH : LOW ) );
  }
  
};

#endif

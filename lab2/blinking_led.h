#ifndef __BLINKING_LED_H__
#define __BLINKING_LED_H__

#include "interval.h"

/*======================================================
| A type of led that blinks accordingly to _interval
======================================================*/
class blinking_led {
  int _pin;
  int _state;
  interval _interval;

  public:
  blinking_led(int pin):
    _pin(pin),
    _state(LOW),
    _interval(10000) {
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

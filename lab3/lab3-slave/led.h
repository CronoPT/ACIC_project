#ifndef __LED_H__
#define __LED_H__

/*======================================================
| A simple led that can be turned on and off
======================================================*/
class led {
  int _pin;

  public:
  led(int pin):_pin(pin) {
    pinMode(_pin, OUTPUT); 
    digitalWrite(_pin, LOW); 
  }

  led(){ /*Do nothing*/ }

  virtual void set_pin(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT); 
    digitalWrite(_pin, LOW);
  }

  virtual void on()  { digitalWrite(_pin, HIGH); }

  virtual void off() { digitalWrite(_pin, LOW);  }
};

#endif

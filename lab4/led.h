#ifndef __LED_H__
#define __LED_H__

class led {
  int _pin;

  public:
  led(int pin):_pin(pin) {
    pinMode(_pin, OUTPUT); 
    digitalWrite(_pin, LOW);
  }

  led(){ /*Do nothing*/ }

  void on()  { digitalWrite(_pin, HIGH); }

  void off() { digitalWrite(_pin, LOW);  }
};

#endif

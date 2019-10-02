#ifndef __BUTTON_H__
#define __BUTTON_H__

class button {
  int _pin;

  public:
  button(int pin):_pin(pin) {
    pinMode(_pin, INPUT);
  }

  button() { } //needed for when you want a button vector

  void set_pin(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
  }

  bool pressed() { return digitalRead(_pin) == HIGH; }
};

#endif

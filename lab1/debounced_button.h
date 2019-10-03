#ifndef __DEBOUNCED_BUTTON_H__
#define __DEBOUNCED_BUTTON_H__

#define DEBOUNCE_DELAY 50

/*
| This class was written based on the web page:
| https://www.arduino.cc/en/Tutorial/debounce
*/

class debounced_button {
  int _pin;
  int _prev_state; 
  int _state; 
  unsigned long _prev_debounce;
  unsigned long _debounce_delay;

  public:
  debounced_button(int pin):
    _pin(pin),
    _prev_state(LOW),
    _state(LOW),
    _prev_debounce(0),
    _debounce_delay(DEBOUNCE_DELAY) {
    pinMode(_pin, INPUT);    
  }

  bool pressed() {
    bool pressed = false;
    int reading = digitalRead(_pin);

    if(reading != _prev_state)
      _prev_debounce = millis();

    if( millis()-_prev_debounce >= _debounce_delay) {
      if(reading != _state) {
        _state = reading;
        if(_state == HIGH)
          pressed = true;
      }
    }
    
    _prev_state = reading;
    return pressed;
  }
};

#endif

#ifndef __PWM_LED_H__
#define __PWM_LED_H__

/*======================================================
| A led whose intensity we can control, for this, it
| must be connected to a pwm pin 
======================================================*/
class pwm_led {
  int _pin; //must be a PWM pin
  int _brightness;
  public:
  pwm_led(int pin):_pin(pin), _brightness(0) {
    pinMode(_pin, OUTPUT);
    analogWrite(_pin, 0);
    
  }
    
  void set_brightness(int brightness) {
    analogWrite(_pin, brightness);
    _brightness = brightness;
  }

  int get_brightness() { return _brightness; }
};

#endif
#ifndef __POTENTIOMETER_H__
#define __POTENTIOMETER_H__

class potentiometer {
  int _pin; //must be an analog pin

  public:
  potentiometer(int pin):_pin(pin) {
    pinMode(_pin, INPUT);    
  }

  int get_read() { 
    return analogRead(_pin);
  }
  
};

#endif

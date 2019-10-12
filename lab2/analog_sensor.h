#ifndef __ANALOG_SENSOR_H__
#define __ANALOG_SENSOR_H__

#define CALIBRATION_TIME 2000

class analog_sensor {
  int _pin; //must be an analog pin
  int _min_reading;
  int _max_reading;

  public:
  analog_sensor(int pin):
    _pin(pin),
    _min_reading(0),
    _max_reading(1023){
    pinMode(_pin, INPUT);
  }

  void callibrate() {
    _min_reading = 1023;
    _max_reading = 0;
    int initial_time = millis();
    while( millis()-initial_time < CALIBRATION_TIME) {
      int reading = get_read();
      _min_reading = _min_reading<reading ? _min_reading : reading;
      _max_reading = _max_reading>reading ? _max_reading : reading; 
    }
  }
  
  int get_read() { 
    return analogRead(_pin);
  }

  int get_read_scaled(int scale_min, int scale_max) {
    int mapped_value = map(get_read(), _min_reading, _max_reading, scale_min, scale_max);
    return constrain(mapped_value, scale_min, scale_max);
  }

  int get_read_scaled_back(int scale_min, int scale_max) {
    int mapped_value = map(get_read(), _max_reading, _min_reading, scale_min, scale_max);
    return constrain(mapped_value, scale_min, scale_max);
  }
  
};

#endif

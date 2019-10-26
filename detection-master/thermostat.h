#ifndef __THERMOSTAT_H__
#define __THERMOSTAT_H__

#include "analog_sensor.h"
#include "schmitt_trigger.h"

#define TEMP_TOLERANCE 1.5

class thermostat {
  analog_sensor _sens;
  schmitt_trigger _trig;

  public:
  thermostat(float temp_thresh, int _pin):
    _sens(_pin),
    _trig(temp_thresh, TEMP_TOLERANCE){ /*Do Nothing*/ }

  bool triggered() { return _trig.triggered( get_temp() ); }
  
  float get_temp() { 
    Serial.println(get_TEMP36_temp());
    return get_TEMP36_temp();
  }

  float get_LM35_temp() {
    return (_sens.get_read()*(5000/1024))/10;
  }

  float get_TEMP36_temp() {
    return (_sens.get_read()*(5.0/1024.0)-0.5)*100;
  }
};

#endif

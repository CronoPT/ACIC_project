#include <Wire.h>
#include "analog_sensor.h"
#include "thermostat.h"

#define POT_PIN   A3
#define LIGHT_PIN A1
#define TEMP_PIN  A0

//the brightness values for the pwm led
#define MAX_BRI 255
#define MIN_BRI 0

//the period values for the led blinking
#define MAX_T 2000 
#define MIN_T 200

#define TEMP_THRESH 17

analog_sensor* pot    = nullptr;
analog_sensor* light  = nullptr;
thermostat*    thermo = nullptr;

/*======================================================
| setup
======================================================*/
void setup() {
  pot    = new analog_sensor(POT_PIN);
  light  = new analog_sensor(LIGHT_PIN);
  thermo = new thermostat(TEMP_THRESH, TEMP_PIN);

  Wire.begin();
  Serial.begin(9600);
  Serial.println("Calibration starting");
  light->callibrate();
  Serial.println("Calibration ending");
}

/*======================================================
| loop
======================================================*/
void loop() {
  set_blinking_led_interval( get_blinking_led_interval() );
  set_pwm_led_brightness(    get_pwm_led_brightness()    );
  set_std_led_state(         get_std_led_state()         );
}

/*======================================================
| tasks
======================================================*/
int get_blinking_led_interval() {
  return pot->get_read_scaled(MIN_T, MAX_T);
}

void set_blinking_led_interval(int interval) {
  Wire.beginTransmission(0x53);
  Wire.write("BLI"); 
  Wire.write( (byte)(interval>>8) ); //second byte counting from the left
  Wire.write( (byte) interval );     //first byte counting from the left
  Wire.endTransmission();
}

int get_pwm_led_brightness() {
  return light->get_read_scaled_backwards(MIN_BRI, MAX_BRI);
}

void set_pwm_led_brightness(int brightness) {
  Wire.beginTransmission(0x53);
  Wire.write("BRI");
  Wire.write( (byte)(brightness>>8) ); //second byte counting from the left
  Wire.write( (byte) brightness );     //first byte counting from the left
  Wire.endTransmission();
}

int get_std_led_state() {
  return thermo->triggered() ? HIGH : LOW;
}

void set_std_led_state(int state) {
  Wire.beginTransmission(0x53);
  Wire.write("STD");
  Wire.write( (byte)(state>>8) ); //second byte counting from the left
  Wire.write( (byte) state );     //first byte counting from the left
  Wire.endTransmission();
}

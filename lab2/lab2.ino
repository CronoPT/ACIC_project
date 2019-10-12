#include "pwm_led.h"
#include "blinking_led.h"
#include "analog_sensor.h"
#include "led.h"

#define PWM_LED_PIN 3
#define BLI_LED_PIN 5
#define STD_LED_PIN 6
#define POT_PIN     A3
#define LIGHT_PIN   A1
#define TEMP_PIN    A0

//the brightness values for the pwm led
#define MAX_BRI 255
#define MIN_BRI 0

//the period values for the led blinking
#define MAX_T 2000 
#define MIN_T 200

#define TEMP_TRESH 24

pwm_led*       pul_led = nullptr;
blinking_led*  bli_led = nullptr;
led*           std_led = nullptr;
analog_sensor* pot     = nullptr;
analog_sensor* light   = nullptr;
analog_sensor* temp    = nullptr;

void setup() {
  pul_led = new pwm_led(PWM_LED_PIN);
  bli_led = new blinking_led(BLI_LED_PIN);
  std_led = new led(STD_LED_PIN);
  pot     = new analog_sensor(POT_PIN);
  light   = new analog_sensor(LIGHT_PIN);
  temp    = new analog_sensor(TEMP_PIN);

  Serial.begin(9600);
  Serial.println("Calibration starting");
  light->callibrate();
  Serial.println("Calibration ending");
}

void loop() {
  set_blinking_led_interval( read_potentiometer()    );
  set_pwm_led_brightness(    read_room_brightness()  );
  set_std_led_state(         read_room_temperature() );
}

double analog_to_temperature(int analog_read) {
  return ((analog_read)*(5.0/1024.0)-0.5)*100;
}

int read_potentiometer() {
  return pot->get_read_scaled(MIN_T, MAX_T);
}

void set_blinking_led_interval(int interval) {
  bli_led->set_interval(interval);
}

int read_room_brightness() {
  return light->get_read_scaled_backwards(MIN_BRI, MAX_BRI);
}

void set_pwm_led_brightness(int brightness) {
  pul_led->set_brightness(brightness);
}

double read_room_temperature() {
  return analog_to_temperature( temp->get_read() );
}

void set_std_led_state(double temperature) {
  if( analog_to_temperature(temp->get_read()) > TEMP_TRESH )
     std_led->on();
  else
    std_led->off();
}

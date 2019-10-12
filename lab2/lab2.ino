#include "pwm_led.h"
#include "blinking_led.h"
#include "analog_sensor.h"

#define PWM_LED_PIN 3
#define BLI_LED_PIN 5
#define POT_PIN     A3
#define LIGHT_PIN   A1

//the brightness values for the pwm led
#define MAX_BRI 255
#define MIN_BRI 0

//the period values for the led blinking
#define MAX_T 2000 
#define MIN_T 200

pwm_led*       pul_led = nullptr;
blinking_led*  bli_led = nullptr;
analog_sensor* pot     = nullptr;
analog_sensor* light   = nullptr;

void setup() {
  pul_led = new pwm_led(PWM_LED_PIN);
  bli_led = new blinking_led(BLI_LED_PIN, MIN_T);
  pot     = new analog_sensor(POT_PIN);
  light   = new analog_sensor(LIGHT_PIN);

  Serial.begin(9600);
  Serial.println("Calibration starting");
  light->callibrate();
  Serial.println("Calibration ending");
}

void loop() {
  int brightness = light->get_read_scaled_back(MIN_BRI, MAX_BRI);
  int interval   = pot->get_read_scaled(MIN_T, MAX_T);
  pul_led->set_brightness(brightness);
  bli_led->set_interval(interval);
}

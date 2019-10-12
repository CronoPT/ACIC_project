#include "pwm_led.h"
#include "blinking_led.h"
#include "potentiometer.h"

#define PWM_LED_PIN 3
#define BLI_LED_PIN 5
#define POT_PIN A3

pwm_led*       pwm_led_ = nullptr;
blinking_led*  bli_led = nullptr;
potentiometer* pot     = nullptr;

void setup() {
  pwm_led_ = new pwm_led(PWM_LED_PIN);
  bli_led  = new blinking_led(BLI_LED_PIN, 200);
  pot = new potentiometer(POT_PIN);
}

void loop() {
  int analog_read = pot->get_read();
  int brightness = map(analog_read, 0, 1023, 0, 255);
  int interval   = map(analog_read, 0, 1023, 200, 2000);
  pwm_led_->set_brightness(brightness);
  bli_led->set_interval(interval);
}

#include <Wire.h>
#include "pwm_led.h"
#include "blinking_led.h"
#include "led.h"

#define PWM_LED_PIN 3
#define BLI_LED_PIN 5
#define STD_LED_PIN 6

pwm_led*      pul_led = nullptr;
blinking_led* bli_led = nullptr;
led*          std_led = nullptr;

/*======================================================
| setup
======================================================*/
void setup() {
  pul_led = new pwm_led(PWM_LED_PIN);
  bli_led = new blinking_led(BLI_LED_PIN);
  std_led = new led(STD_LED_PIN);
}

/*======================================================
| loop
======================================================*/
void loop() {

}

/*======================================================
| tasks
======================================================*/
void set_blinking_led_interval(int interval) {
  /*So something with wire*/
  bli_led->set_interval(interval);
}

void set_pwm_led_brightness(int brightness) {
  /*So something with wire*/
  pul_led->set_brightness(brightness);
}

void set_std_led_state(double temperature) {
  /*So something with wire*/
  if( analog_to_temperature(temp->get_read()) > TEMP_TRESH )
     std_led->on();
  else
    std_led->off();
}

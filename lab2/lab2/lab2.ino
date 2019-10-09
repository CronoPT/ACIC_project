#include "act_led.h"
#include "sen_potentiometer.h"

#define LED_PIN 3
#define POT_PIN A3

act_led* led = nullptr;
sen_potentiometer* pot = nullptr;

void setup() {
  led = new act_led(LED_PIN);
  pot = new sen_potentiometer(POT_PIN);
}

void loop() {
  led->activate(pot->activated());

}

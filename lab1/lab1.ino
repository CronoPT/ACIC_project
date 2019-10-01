#include "button.h"
#include "led.h"

#define LEDS 4
#define INTERVAL 1000
#define BUTTON_PIN 8

int led_pins[] = {2, 3, 4, 5};
led leds[LEDS]; 
button button;

unsigned long prev_millis = 0;
unsigned long curr_millis = 0;
int led_on = 0;

void setup() {
  for(int i=0; i<LEDS; i++) {
    leds[i].set_pin(led_pins[i]);
  }

  button.set_pin(BUTTON_PIN);
}

void loop() {

  curr_millis = millis();
  if( curr_millis-prev_millis >= INTERVAL ){
    prev_millis = curr_millis;

    if(led_on == LEDS) {
      for(int i=0; i<LEDS; i++) {
        leds[i].off();
      }
      led_on = -1; //just because led_on++ will run after
    }
    else if(led_on != -1) {
      leds[led_on].on();
    }

    led_on += 1;
  }
 
}

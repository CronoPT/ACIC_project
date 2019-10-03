#include "led.h"
#include "null_led.h"
#include "interval.h"
#include "debounced_button.h"

#define LEDS 4
#define INTERVAL 1000
#define BUTTON_PIN 8

led* leds[LEDS+1];

int led_pins[] = {2, 3, 4, 5};
int led_on     = 0;
int led_off    = LEDS;

interval led_interval    = interval(INTERVAL);
debounced_button* button = nullptr;

bool blinking = true;

/*==============================================================
| setup
==============================================================*/
void setup() {
  for(int i=0; i<LEDS; i++)
    leds[i]  = new led(led_pins[i]);
  leds[LEDS] = new null_led(); 
  button     = new debounced_button(BUTTON_PIN);
}

/*==============================================================
| loop
==============================================================*/
void loop() {
  if( button->pressed() ) {
    if(blinking)
      led_interval.freeze();
    else
      led_interval.unfreeze();
    blinking = !blinking;
  }
  
  if(blinking) {
    if( led_interval.passed() ){
      leds[led_on]->on();
      leds[led_off]->off();
      
      led_on  = (led_on +1) % (LEDS+1);
      led_off = (led_off+1) % (LEDS+1);
    }
  }
}

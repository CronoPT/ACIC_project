#include "button.h"
#include "led.h"
#include "null_led.h"

#define LEDS 4
#define INTERVAL 1000
#define BUTTON_PIN 2

int led_pins[] = {3, 4, 5, 6};
led* leds[LEDS+1];

unsigned long prev_millis = 0;
unsigned long curr_millis = 0;
unsigned long time_gap    = 0; 

int led_on  = 0;
int led_off = LEDS;

bool blinking = true;

void setup() {

  attachInterrupt( digitalPinToInterrupt(BUTTON_PIN), call_back, RISING);
  
  for(int i=0; i<LEDS; i++) {
    leds[i] = new led(led_pins[i]);
  }
  leds[LEDS] = new null_led();
  
  Serial.begin(9600);
}

void loop() {
  
  curr_millis = millis();
  if(blinking) {
    if( curr_millis-prev_millis >= INTERVAL ){
      prev_millis = curr_millis;
  
      leds[led_on]->on();
      leds[led_off]->off();
      
      led_on  = (led_on +1) % LEDS+1;
      led_off = (led_off+1) % LEDS+1;
    }
  }
  
}

void call_back() {
  curr_millis = millis();
  if(blinking)
    time_gap = curr_millis - prev_millis;
  else
    prev_millis = millis() - time_gap;
  blinking = !blinking;
}

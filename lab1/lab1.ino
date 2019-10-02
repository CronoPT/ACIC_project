#include "button.h"
#include "led.h"

#define LEDS 4
#define INTERVAL 1000
#define BUTTON_PIN 2

int led_pins[] = {3, 4, 5, 6};
led leds[LEDS]; 

unsigned long prev_millis = 0;
unsigned long curr_millis = 0;
unsigned long time_gap    = 0; 
int led_on = 0;

bool blinking = true;

void setup() {

  attachInterrupt( digitalPinToInterrupt(BUTTON_PIN), call_back, RISING);
  for(int i=0; i<LEDS; i++) {
    leds[i].set_pin(led_pins[i]);
  }
  Serial.begin(9600);
}

void loop() {
  
  curr_millis = millis();
  if(blinking) {
    if( curr_millis-prev_millis >= INTERVAL ){
      prev_millis = curr_millis;
  
      if(led_on == LEDS) {
        for(int i=0; i<LEDS; i++)
          leds[i].off();
        led_on  = -1; //just because led_on++ will run after
      }
      else if(led_on != -1) {
        leds[led_on].on();
        if(led_on-1 >= 0)
          leds[led_on-1].off();
      }
  
      led_on  += 1;
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

#include "led.h"
#include "null_led.h"
#include "interval.h"

#define LEDS 4
#define INTERVAL 1000
#define BUTTON_PIN 2

led* leds[LEDS+1];

int led_pins[] = {3, 4, 5, 6};
int led_on     = 0;
int led_off    = LEDS;

interval led_interval = interval(INTERVAL);

bool blinking = true;

/*==============================================================
| setup
==============================================================*/
void setup() {
  Serial.begin(9600);
  attachInterrupt( digitalPinToInterrupt(BUTTON_PIN), call_back, RISING);
  
  for(int i=0; i<LEDS; i++)
    leds[i]  = new led(led_pins[i]);
  leds[LEDS] = new null_led(); 
}

/*==============================================================
| loop
==============================================================*/
void loop() {
  if(blinking) {
    if( led_interval.passed() ){
      leds[led_on]->on();
      leds[led_off]->off();
      
      led_on  = (led_on +1) % LEDS+1;
      led_off = (led_off+1) % LEDS+1;
    }
  }
}

/*==============================================================
| call_back
==============================================================*/
void call_back() {
  if(blinking)
    led_interval.freeze();
  else
    led_interval.unfreeze();
  blinking = !blinking;
}

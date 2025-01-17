/*======================================================
| EXERCISE 5
======================================================*/
void set_blinking_led_interval(int interval) {
  bli_led->set_interval(interval);
}

void set_pwm_led_brightness(int brightness) {
  pul_led->set_brightness(brightness);
}

void set_std_led_state(int state) {
  state ? std_led->on() : std_led->off();
}
#include <Wire.h>
#include "pwm_led.h"
#include "blinking_led.h"
#include "led.h"

#include "analog_sensor.h"

#define PWM_LED_PIN 5
#define BLI_LED_PIN 3
#define STD_LED_PIN 2

#define LED_DETECT_PIN A2

#define ANALOG_NOISE 50

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

  
  pinMode(LED_DETECT_PIN,INPUT);


  Serial.begin(9600);
  
  Wire.begin(0x53);
  Wire.onRequest(send_led_state);
  Wire.onReceive(react_to_sensors);
}

/*======================================================
| loop
======================================================*/
void loop() { /*Do Nothing*/ }

/*======================================================
| react_to_sensors, aka handler
======================================================*/
void react_to_sensors(int numBytes) {
  String command = String("");
  for(int i=0; i<3; i++)
    command += (char) Wire.read();
  int res = (int)Wire.read();
  res = (res<<8) + (int)Wire.read();
  
  if(command == "BLI")
    set_blinking_led_interval(res);
  else if(command == "BRI")
    {set_pwm_led_brightness(res);
     
     }
  else if(command == "STD")
    set_std_led_state(res);
}

/*======================================================
| tasks
======================================================*/
void set_blinking_led_interval(int interval) {
  bli_led->set_interval(interval);
}

void set_pwm_led_brightness(int brightness) {
  pul_led->set_brightness(brightness);
}

void set_std_led_state(int state) {
  state ? std_led->on() : std_led->off();
}

/*======================================================
| begining of changes to EXERCISE 5
======================================================*/
char detect_led_state() {
  double input = 0;
  
  for(int i=0; i<100; i++)
    //reading the analog values, they seemed noisy, so we could not compare
    //them with zero, because we never read a zero
    input += analogRead(LED_DETECT_PIN)>ANALOG_NOISE ? 1 : 0;
    
  input = input*5/100;
  
  if( pul_led->get_brightness()!=0 && input==0 ) {
    Serial.println("broke");
    return 'b';
  }
  else {
    Serial.println("ok");
    return 'o';
  }     
}

//just sends a byte indicating if the led is OK or BROKE
void send_led_state() {
  char state = detect_led_state();
  Wire.write((byte)state);
}
/*======================================================
| ending of changes to EXERCISE 5
======================================================*/

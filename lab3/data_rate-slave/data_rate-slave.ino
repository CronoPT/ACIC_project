#include <Wire.h>

#define BYTES_PER_LOOP 100

/*======================================================
| setup
======================================================*/
void setup() {
  Serial.begin(9600);
  
  Wire.begin(0x53);
  Wire.onReceive(say_something);
}

/*======================================================
| loop
======================================================*/
void loop() { /*Do Nothing*/ }

/*======================================================
| react_to_sensors, aka handler
======================================================*/
void say_something(int numBytes) {
  Serial.println("=================================");
  while( Wire.available() )
    Serial.println( (char)Wire.read() );
}

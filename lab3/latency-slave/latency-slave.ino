#include <Wire.h>

bool go_on = false;

/*======================================================
| setup
======================================================*/
void setup() {
  Serial.begin(9600);
  
  Wire.begin(0x53);
  Wire.onReceive(say_something);
  Wire.onRequest(do_something);
}

/*======================================================
| loop
======================================================*/
void loop() { /*Do Nothing*/ }

void say_something(int numBytes) {
  Wire.read();
  go_on = true;
}

void do_something() {
  Wire.write( (byte)'a' );
  while(!go_on);
  go_on = false;
}

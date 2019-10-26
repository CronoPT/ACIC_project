#include <Wire.h>

#define REPETITIONS 100

unsigned long initial_t = 0;
unsigned long run_t     = 0;
unsigned long mean_t    = 0;

/*======================================================
| setup
======================================================*/
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

/*======================================================
| loop
======================================================*/
void loop() {
  mean_t = 0;

  for(int i=0; i<REPETITIONS; i++) {
    initial_t = micros();
    Wire.beginTransmission(0x53);
    Wire.write( (byte)'a' );
    Wire.endTransmission();
    Wire.requestFrom(0x53, 1);
    Wire.read();
    run_t = micros() - initial_t;
    mean_t += run_t;
  }
  Serial.print("Mean for latency");
  Serial.print(" : ");
  double useconds_per_byte = (mean_t/REPETITIONS);
  Serial.println( useconds_per_byte/2 );

}

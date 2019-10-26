#include <Wire.h>

#define BYTES_PER_LOOP 100
#define REPETITIONS    100

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
  for(int j=0; j<REPETITIONS; j++) {
    initial_t = millis();
    Wire.beginTransmission(0x53);
    for(int i=0; i<BYTES_PER_LOOP; i++) {
      Wire.write( "a" );
    }
    Wire.endTransmission();
    run_t = millis() - initial_t;
    mean_t += run_t;
  }
  Serial.print("Mean for ");
  Serial.print(BYTES_PER_LOOP);
  Serial.print(" : ");
  double aux = (mean_t/REPETITIONS);
  double useconds_per_byte = aux/BYTES_PER_LOOP;
  Serial.println( useconds_per_byte );
}

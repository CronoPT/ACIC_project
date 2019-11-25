
#include "intersept.h"

#define MODE_0 0
#define MODE_1 1
#define MODE_2 2

intersept* interseption = nullptr;

void setup() {
  /*
   | Read interseption info
   | Initialize interseption
  */
  Serial.begin(9600);
  interseption = new intersept(MODE_2);
}

void loop() { interseption->operate(); }

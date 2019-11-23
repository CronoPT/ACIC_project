
#include "intersept.h"

#define MODE_0 0
#define MODE_1 1
#define MODE_2 2

void setup() {
  /*
   | Read interseption info
   | Initialize interseption
  */
  intersept interseption = new intersept(x, y, s, w, s_but_pin, w_but_pin, MODE_0)
}

void loop() { interseption->operate(); }

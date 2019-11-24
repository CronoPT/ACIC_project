#ifndef __MODE_1_H__
#define __MODE_1_H__

#include "intersept_mode.h"

class mode_1: public intersept_mode {

  public:
  mode_1(intersept* interseption):
    intersept_mode(interseption) { /*Do Nothing*/ }
    
  void operate() override {
    //FIXME: implement
  }
  
};

#endif

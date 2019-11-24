#ifndef __MODE_0_H__
#define __MODE_0_H__

#include "intersept_mode.h"

class mode_0: public intersept_mode {
  
  public:
  mode_0(intersept* interseption):
    intersept_mode(interseption) { /*Do Nothing*/ Serial.println("Building intersept mode 0");}
    
  void operate() override;
  
};

#endif

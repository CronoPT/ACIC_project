#ifndef __MODE_2_H__
#define __MODE_2_H__

#include "intersept_mode.h"

class mode_2: public intersept_mode {

  public:
  mode_2(intersept* interseption):
    intersept_mode(interseption) { /*Do Nothing*/ }
    
  void operate() override ;
  
};

#endif

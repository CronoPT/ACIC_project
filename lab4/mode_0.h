/* FILENAME - mode_0.h */

#ifndef __MODE_0_H__
#define __MODE_0_H__

#include "intersept_mode.h"

class mode_0: public intersept_mode {
  
  public:
  mode_0(intersept* interseption);
  void operate() override ;
};

#endif

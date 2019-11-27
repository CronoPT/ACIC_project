/* FILENAME - mode_malfunction.h */

#ifndef __MODE_MALFUNCTION_H__
#define __MODE_MALFUNCTION_H__

#include "intersept_mode.h"

class mode_malfunction: public intersept_mode {
  /* Previous mode to return to */
  intersept_mode* _prev;

  /*
  | True if the broken led was in the south 
  | direction
  | False if the broken led was in the west
  | direction
  */
  bool _broke_s;

  public:
  mode_malfunction(intersept* interseption,
                   intersept_mode* prev,
                   bool broke_s);
  void operate() override ;
};

#endif

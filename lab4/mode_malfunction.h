#ifndef __MODE_MALFUNCTION_H__
#define __MODE_MALFUNCTION_H__

#include "intersept_mode.h"

class mode_malfunction: public intersept_mode {
  intersept_mode* _prev;
  bool _broke_s;

  public:
  mode_malfunction(intersept* interseption,
                   intersept_mode* prev,
                   bool broke_s);
  void operate() override ;
};

#endif

#ifndef __MODE_MALFUNCTION_H__
#define __MODE_MALFUNCTION_H__

#include "intersept_mode.h"

class mode_malfunction: public intersetp_mode {
  intersept_node* _prev;
  bool _broke_s;

  public:
  mode_malfunction(intersept* interseption,
                   intersept_mode* prev,
                   bool broke_s);
  void operate() override ;
};

#endif

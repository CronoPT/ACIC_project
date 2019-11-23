#ifndef __INTERSEPT_MODE_H__
#define __INTERSEPT_MODE_H__

#include "intersept.h"

class intersept_mode {
  intersept* _interseption;

  protected:
  intersept_mode(intersept* interseption):
    _interseption(interseption) { /*Do Nothing*/ }
  
  public:
  virtual void operate() = 0;

  intersept* get_intersep() const { return _intersept; }
  
};

#endif

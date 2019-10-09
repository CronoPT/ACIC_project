#ifndef __ACTUATOR_H__
#define __ACTUATOR_H__

class actuator {
  public:
  virtual void activate(int analog_read) = 0;
};

#endif

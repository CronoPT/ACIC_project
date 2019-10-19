#ifndef __SCHMITT_TRIGGER_H__
#define __SCHMITT_TRIGGER_H__

class schmitt_trigger {
  float _thresh;
  float _tolerance;
  bool _triggered;

  public:
  schmitt_trigger(float thresh, float tolerance):
    _thresh(thresh),
    _tolerance(tolerance),
    _triggered(false){ /*Do Nothing*/ }

  bool triggered(float reading) {
    if(_triggered)
      _triggered = reading + _tolerance >= _thresh;
    else
      _triggered = reading - _tolerance >= _thresh;

    return _triggered;
  }
  
};

#endif

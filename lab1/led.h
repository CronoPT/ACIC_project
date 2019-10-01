
class led {
  int _pin;

  public:
  led(int pin):_pin(pin){
    pinMode(_pin, OUTPUT); 
    digitalWrite(_pin, LOW); 
  }

  led(){ } //needed for when you want a led vector

  void set_pin(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT); 
    digitalWrite(_pin, LOW);
  }

  void on(){ digitalWrite(_pin, HIGH); }

  void off(){ digitalWrite(_pin, LOW); }
};

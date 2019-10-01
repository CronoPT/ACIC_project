
class button {
  int _pin;

  public:
  button(int pin):_pin(pin) {
    pinMode(_pin, INPUT);
  }

  button() { } //needed for when you want a button vector

  void set_pin(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
  }

  bool button_pressed() { return digitalRead(_pin) == LOW; }
};

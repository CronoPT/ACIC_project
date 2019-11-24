#ifndef __I2C_POST_OFFICE_H__
#define __I2C_POST_OFFICE_H__

#include <Wire.h>

class message;

class i2c_post_office {
  message* _msgs[4];
  int _index = 0;
  int _max_index = 4;
  i2c_post_office() { /*Do Nothing*/ }

  public:
  static i2c_post_office& get_instance() {
      static i2c_post_office instance;
      return instance;
  }

  void init_post_office();
  void send_message(message* msg);
  message* receive_message();
  message* get_latest();
  void add_message(message* msg);

  int get_index() const { return _index; }
  int get_max_index() const { return _max_index; }

};

#endif

#ifndef __I2C_POST_OFFICE_H__
#define __I2C_POST_OFFICE_H__

#include <Wire.h>
#include "queue.h"

class message;

class i2c_post_office {
  queue _queue;
  i2c_post_office():_queue() { /*Do Nothing*/ }

  public:
  static i2c_post_office& get_instance() {
      static i2c_post_office instance;
      return instance;
  }

  i2c_post_office(i2c_post_office const&);
  void operator=(i2c_post_office const&);

  void init_post_office(byte address);
  void send_message(message* msg);
  message* receive_message();
  message* get_latest();
  void add_message(message* msg);
  bool has_messages();

};

#endif

#include "i2c_post_office.h"
#include "message.h"

/*===================================================================
| on_receive:
|   * params:
|     * num_bytes -> number of bytes received over the I2C bus
|   * returns nothing
|
| Receives a message over the I2C bus and adds tha message to 
| the i2c_post_office
===================================================================*/
void on_receive(int num_bytes) {
  byte destination = (byte) Wire.read();
  byte source = (byte) Wire.read(); 
  byte event  = (byte) Wire.read();
  byte cars_N = (byte) Wire.read();
  byte cars_S = (byte) Wire.read();
  byte cars_E = (byte) Wire.read();
  byte cars_W = (byte) Wire.read();
  unsigned long time_stamp = (long) Wire.read();
  time_stamp = (time_stamp<<8) + Wire.read(); 
  time_stamp = (time_stamp<<8) + Wire.read(); 
  time_stamp = (time_stamp<<8) + Wire.read(); 
  message* res = new message(destination, source, event, cars_N, cars_S, cars_E,
                              cars_W, time_stamp);
  i2c_post_office::get_instance().add_message(res);
}

/*===================================================================
| init:
|   * params:
|     * address -> address of the node that will be receiving and
|       sending messages over this post office
|   * returns nothing
|
| Just initiate the I2C interface
===================================================================*/
void i2c_post_office::init_post_office(byte address) {
    Wire.begin(address);
    Wire.onReceive(on_receive);
}

/*===================================================================
| send:
|   * params:
|     * msg -> message to send over the I2C
|   * returns nothing
|
| This fucntion will run on the main loop of the program and it is 
| reponsible for implementing the behavior associated with
| mode_2
===================================================================*/
void i2c_post_office::send_message(message* msg) {
  Wire.beginTransmission(msg->get_destination());
  Wire.write((byte) msg->get_destination());
  Wire.write((byte) msg->get_source());
  Wire.write((byte) msg->get_event());
  Wire.write((byte) msg->get_cars_N());
  Wire.write((byte) msg->get_cars_S());
  Wire.write((byte) msg->get_cars_E());
  Wire.write((byte) msg->get_cars_W());
  unsigned long stamp = millis();
  Wire.write((byte)(stamp>>24));
  Wire.write((byte)(stamp>>16));
  Wire.write((byte)(stamp>>8));
  Wire.write((byte) stamp);
  Wire.endTransmission();
}

/*===================================================================
| operate:
|   * params:
|     * msg -> message to add to the post office (queue)
|   * returns nothing
|
| Put the message in the queue
===================================================================*/
void i2c_post_office::add_message(message* msg) {
  _queue.push_back(msg);
}

/*===================================================================
| operate:
|   * params none
|   * returns:
|     * message -> the next message in the message queue
|
| Pop the queue
===================================================================*/
message* i2c_post_office::get_latest() {
  return _queue.pop();
}
 /*===================================================================
| operate:
|   * params none
|   * returns
|     * bool -> indicating whether there are messages or not
|
| Check if the queue is empty
===================================================================*/
bool i2c_post_office::has_messages() {
  return !_queue.empty();
}

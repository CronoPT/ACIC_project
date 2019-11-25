#include "i2c_post_office.h"
#include "message.h"

void on_receive(int num_bytes) {
  i2c_post_office::get_instance().add_message( i2c_post_office::get_instance().receive_message() );
}

void i2c_post_office::init_post_office(byte address) {
    Wire.begin(address);
    Wire.onReceive(on_receive);
}

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
  Serial.println("Ending transmission");
  Wire.endTransmission();
  Serial.println("Endededed transmission");
}

message* i2c_post_office::receive_message() {
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
    return res;
}

void i2c_post_office::add_message(message* msg) {
  _queue.push_back(msg);
}

message* i2c_post_office::get_latest() {
  return _queue.pop();
}

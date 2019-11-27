/* FILENAME - message.h */

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "Arduino.h"

//DTO - data transfer object
class message {
  byte _destination;
  byte _source;
  byte _event;
  byte _cars_N;
  byte _cars_S;
  byte _cars_E;
  byte _cars_W;
  unsigned long _time_stamp;

  public:
  message(byte destination, byte source, byte event, byte cars_N,
            byte cars_S, byte cars_E, byte cars_W):
    _destination(destination),
    _source(source),
    _event(event),
    _cars_N(cars_N),
    _cars_S(cars_S),
    _cars_E(cars_E),
    _cars_W(cars_W),
    _time_stamp(0) { /*Do Nothing*/ }

  message(byte destination, byte source, byte event, byte cars_N,
          byte cars_S, byte cars_E, byte cars_W, unsigned long time_stamp):
    _destination(destination),
    _source(source),
    _event(event),
    _cars_N(cars_N),
    _cars_S(cars_S),
    _cars_E(cars_E),
    _cars_W(cars_W),
    _time_stamp(time_stamp) { /*Do Nothing*/ }

  void print() {
    Serial.println("==========NEW_MESSAGE==========");
    Serial.print("Destination: ");
    Serial.println(_destination);
    Serial.print("Source: ");
    Serial.println(_source);
    Serial.print("Event: ");
    Serial.println(_event);
    Serial.print("Cars North: ");
    Serial.println(_cars_N);
    Serial.print("Cars South: ");
    Serial.println(_cars_S);
    Serial.print("Cars East: ");
    Serial.println(_cars_E);
    Serial.print("Cars West: ");
    Serial.println(_cars_W);
    Serial.print("Stamp: ");
    Serial.println(_time_stamp);
    Serial.println("==============================="); 
  }

  byte get_destination() const { return _destination; }
  byte get_source() const { return _source; }
  byte get_event()  const { return _event;  }
  byte get_cars_N() const { return _cars_N; }
  byte get_cars_S() const { return _cars_S; }
  byte get_cars_E() const { return _cars_E; }
  byte get_cars_W() const { return _cars_W; }
  unsigned long get_time_stamp() const { return _time_stamp; }
  void set_time_stamp(unsigned long time_stamp) { _time_stamp = time_stamp; }

};

#endif

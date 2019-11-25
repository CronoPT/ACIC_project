
#include "intersept.h"
#include "queue.h"
#include "message.h"

#define MODE_0 0
#define MODE_1 1
#define MODE_2 2

intersept* interseption = nullptr;

void setup() {
  Serial.begin(9600);
  /*
  message* msg_1 = new message(0, 0, 0, 0, 0, 0, 0, 0);
  message* msg_2 = new message(0, 0, 0, 0, 0, 0, 0, 0);
  message* msg_3 = new message(0, 0, 0, 0, 0, 0, 0, 0);
  message* msg_4 = new message(0, 0, 0, 0, 0, 0, 0, 0);
  queue q;
  q.push_back(msg_1);
  q.push_back(msg_2);
  q.push_back(msg_3);
  q.push_back(msg_4);
  message* j = q.pop();
  Serial.println(j==msg_1 ? "Passed" : "Not passed");
  j = q.pop();
  Serial.println(j==msg_2 ? "Passed" : "Not passed");
  j = q.pop();
  message* msg_5 = new message(0, 0, 0, 0, 0, 0, 0, 0);
  q.push_back(msg_5);
  Serial.println(j==msg_3 ? "Passed" : "Not passed");
  j = q.pop();
  Serial.println(j==msg_4 ? "Passed" : "Not passed");
  Serial.println(q.empty() ? "Not passed" : "Passed");
  j = q.pop();
  Serial.println(j==msg_5 ? "Passed" : "Not passed");
  Serial.println(q.empty() ? "Passed" : "Not passed");*/
  
  interseption = new intersept(MODE_2);
}

void loop() { interseption->operate(); }

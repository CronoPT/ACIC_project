/* FILENAME - queue.cpp */

#include "queue.h"

bool queue::empty() {
  return _head == nullptr;
}

message* queue::pop() {
  if(empty()) 
    return nullptr;

  node* curr_node = _head;
  _head = curr_node->get_next();
  message* msg = curr_node->get_msg();
  if(_back==curr_node)
    _back = nullptr;
  delete curr_node;
  return msg;
}

void queue::push_back(message* msg) {
  node* curr_node = new node(msg, nullptr);
  if(_back!=nullptr) 
    _back->set_next(curr_node);
  _back = curr_node;

  if(_head==nullptr) 
    _head = curr_node;
}



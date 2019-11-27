/* FILENAME - queue.h */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "message.h"

class node {
	message* _msg;
	node*    _next;

	public:
	node(message* msg, node* next):
		_msg(msg), _next(next) { /*Do Nothing*/ }

	message* get_msg() const { return _msg; }
	node* get_next() const { return _next; }
	void set_next(node* next) { _next = next; }
};

class queue {
	node* _head;
	node* _back;

	public:
	queue():_head(nullptr), _back(nullptr) {
		/*Do Nothing*/
	}

	bool empty();
	message* pop();
	void push_back(message* msg);

};

#endif

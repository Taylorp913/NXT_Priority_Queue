#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <list>
#include "Message.h"

using namespace std;
#pragma once
extern "C"
{
#include "kernel.h"
#include "ecrobot_interface.h"
}




//#############################################################################
// Priority Queue
//
// A priority based Message Queue.
// This queue manages pointers to messages do not pass pointer to messages
// allocated on the stack.  The user is required to manage the memory explicitly.
//
// some task.run(...)
// {
// 		...
// 		router->registerTaskQueue(task, &pQueue);
// 		while (1) {
// 			...
// 			MyMsg* m = new MyMsg(...);	// do not use MyMsg m(...);
// 			router->SendMsg(m);
// 		}
// }
// 
// some other Task run(...)
// {
// 	Message* mPtr = NULL;
// 	while ((mPtr = pQueue.dequeueMessage()) != NULL)
// 	{
// 		...
//		delete mPtr;
// 	}
// }

//#############################################################################
class PriorityQueue
{
public:
	static const U8 MAX_ELEMENTS_P1 = 10;		// max number of elements in each priority 
	static const U8 MAX_ELEMENTS_P2 = 10;		// max number of elements in each priority 
	static const U8 MAX_ELEMENTS_P3 = 10;		// max number of elements in each priority 
	
	PriorityQueue();
	~PriorityQueue() { clear(); }
	bool isEmpty();
	bool enqueueMessage(Message* message);
	Message* dequeueMessage();
	int getCount();
	void setResource(ResourceType resId);
	void clear();



protected:
	list<Message*> priority1List;
	list<Message*> priority2List;
	list<Message*> priority3List;
	ResourceType resourceId;
	int queuedItemsCount;
};

#endif

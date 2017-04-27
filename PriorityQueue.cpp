#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
	queuedItemsCount = 0;
}

void PriorityQueue::clear()
{
	GetResource(resourceId);
	queuedItemsCount = 0;
	priority1List.clear();
	priority2List.clear();
	priority3List.clear();
	ReleaseResource(resourceId);
}

//Returns true if the queue is empty, false if not
bool PriorityQueue::isEmpty()
{
	return (queuedItemsCount == 0);
}

// Queues the given message if the queue isn't full, drops the message if not.
// Also, only supports messages with priority of low, med or high, others are dropped.
// Returns success if the message was inserted into the queue
bool PriorityQueue::enqueueMessage(Message* msgPtr)
{
	// make a clone and store the pointer to the clone in the queue
	bool success = false;
	GetResource(resourceId);

	switch(msgPtr->priority)
	{
	case MsgPriority::LOW:	
		if (priority1List.size() < MAX_ELEMENTS_P1)
		{
			priority1List.push_back(msgPtr);
			queuedItemsCount++;
			success = true;
		}
		break;
	case MsgPriority::MED:
		if (priority2List.size() < MAX_ELEMENTS_P2)
		{
			priority2List.push_back(msgPtr);
			queuedItemsCount++;
			success = true;
		}
		break;
	case MsgPriority::HIGH:
		if (priority3List.size() < MAX_ELEMENTS_P3)
		{
			priority3List.push_back(msgPtr);
			queuedItemsCount++;
			success = true;
		}
		break;

	//priority must be low, med, high
	default:
		break;
	}
	ReleaseResource(resourceId);

	return success;
}

// Dequeues the next message 
// The Caller is responsible for managing the memory and deleting the pointer when finished
//		delete msg;
// returns a pointer to the message, or null if none
Message* PriorityQueue::dequeueMessage()
{
	Message* msgPtr = NULL;

	GetResource(resourceId);
	if(queuedItemsCount > 0)
	{
		if(!priority3List.empty())
		{
			msgPtr = priority3List.front();  // get
			priority3List.pop_front();  // remove
		}
		else if(!priority2List.empty())
		{
			msgPtr = priority2List.front();
			priority2List.pop_front();
		}
		else if(!priority1List.empty())
		{
			msgPtr = priority1List.front();
			priority1List.pop_front();
		}
		queuedItemsCount--;				// decrement
	}
	ReleaseResource(resourceId);

	return msgPtr;
}

int PriorityQueue::getCount()
{
	return queuedItemsCount;
}

// TODO: comment this!
void PriorityQueue::setResource(ResourceType resId)
{
	resourceId = resId;
}

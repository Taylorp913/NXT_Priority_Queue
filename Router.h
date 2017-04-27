#ifndef Router_H
#define Router_H

#include <list>
#include "Message.h"
#include "PriorityQueue.h"
using namespace std;

struct TaskQueue
{
	PriorityQueue* queue;
	TaskId::Type taskId;
};

class Router
{	
public:
	~Router() { taskQueues.clear(); };
	void registerTaskQueue(TaskId::Type taskId, PriorityQueue* queue);
	ErrorCode::Type SendMessage(Message* m);


protected:
	list<TaskQueue> taskQueues;
};
#endif /*Router_H*/


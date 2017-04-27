#include "Router.h"

void Router::registerTaskQueue(TaskId::Type taskId, PriorityQueue* queue)
{
	TaskQueue t;
	t.taskId = taskId;
	t.queue = queue;
	taskQueues.push_back(t);
}

ErrorCode::Type Router::SendMessage(Message* m)
{
	if (m == NULL) return ErrorCode::NullMsgReceived;
	

	ErrorCode::Type err = ErrorCode::InvalidDestination;
	list<TaskQueue>::iterator it;
	for(it = taskQueues.begin(); it != taskQueues.end(); it++)
	{
		if(it->taskId == m->destId)
		{
			// we are combining the error of not being able to insert
			// into the queue and not finding the detination into the same result
			if (it->queue->enqueueMessage(m))
				return ErrorCode::None;
			else
				return ErrorCode::PQueueFull;
		}
	}

	return err;
}

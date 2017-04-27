#ifndef MyTask_H
#define MyTask_H

#include <string.h>
#include "Router.h"
#include "PriorityQueue.h"
#include "Message.h"
#pragma once
	
extern "C"
{
	#include "kernel.h"
	#include "ecrobot_interface.h"
};
	     
class MyTask
{
public:
	MyTask(void) : count(0), lastStatusSeqNum(0), state(TaskState::Init), router(NULL)
	{
		memset(name, '\0', 10);
	}
	
	virtual ~MyTask() {}
	
	// initialize the object
	virtual S8 init(char* name, Router* router, ResourceType resId, TaskId::Type task);

	// run the task
	virtual S8 run(void);
	
	// Get the run counter
	virtual S16 getCount(void);
	
	// Get the state of the task
	virtual TaskState::Type getState(void);

	// Get the task name
	char* getName(void);

protected:
	S16 count;
	U8 lastStatusSeqNum;
	TaskState::Type state;
	char name[10];
	Router* router;
	PriorityQueue queue;
};

#endif /*My_Task_H*/


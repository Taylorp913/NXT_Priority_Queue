#include "MyTask.h"

// Initialize the Task
S8 MyTask::init(char* name, Router* router2, ResourceType resId, TaskId::Type task)
{
	state = TaskState::Init;

	// do thread initialization
	strcpy(name, name);
	router = router2;
	queue.clear();
	queue.setResource(resId);
	router->registerTaskQueue(task, &queue);
	
	return 1;
}

// Do main processing
S8 MyTask::run(void)
{
	S8 success = 1;

	if (state == TaskState::Init) state = TaskState::Running;
	
	// do normal thread processing
	count++;
	
	return success;
}

// Get the current run count.
S16 MyTask::getCount(void)
{	
	return count;
}

// Get the current run count.
char* MyTask::getName(void)
{	
	return name;
}

// Get the current run count.
TaskState::Type MyTask::getState(void)
{
	return state;
}

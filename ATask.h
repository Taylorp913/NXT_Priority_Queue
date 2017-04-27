#ifndef ATask_H
#define ATask_H

#include "MyTask.h"
#pragma once

class ATask : public MyTask
{	
public:
	ATask();
	// run the task
	virtual S8 run(void);

private:
	U8 lastSeqNum;
	bool isLastCommandComplete;
	U8 rxCount;
};
#endif /*ATask_H*/


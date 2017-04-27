#ifndef BTask_H
#define BTask_H


#include "MyTask.h"
#pragma once

class BTask : public MyTask
{	
public:
	BTask();

	// run the task
	virtual S8 run(void);

private:
	U8 lastSeqNum;
	U8 rxCount;
};

#endif /*BTask_H*/

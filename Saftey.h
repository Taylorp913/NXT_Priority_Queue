#ifndef SAFTEYTask_H
#define SAFTEYTask_H

#include "MyTask.h"
#pragma once

class SAFTEYTask : public MyTask
{
public:
	SAFTEYTask();
	// run the task
	virtual S8 run(void);

private:
	U8 lastSeqNum;
	U8 rxCount;
};

#endif /*SAFTEYTask_H*/

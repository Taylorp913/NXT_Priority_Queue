#ifndef DisplayTask_H
#define DisplayTask_H


#include "MyTask.h"
#pragma once

class DisplayTask : public MyTask
{	
public:
	// run the task
	virtual S8 run(void);

private:
	ErrorCode::Type lastErrorCode;
};

#endif /*DisplayTask_H*/

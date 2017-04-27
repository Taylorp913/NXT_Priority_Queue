
// ECRobot++ API
#include "Clock.h"
#include <cstring>
#include "ATask.h"
#include "BTask.h"
#include "Saftey.h"
#include "DisplayTask.h"
#include "Router.h"
using namespace std;

//#include <Lcd.h>

//ecrobot::Lcd lcd;

extern "C"
{
	#include "kernel.h"
	#include "kernel_id.h"
	#include "ecrobot_interface.h"
	
	ATask aTask;
	BTask bTask;
	SAFTEYTask safteyTask;
	DisplayTask displayTask;

	//declare tasks
	DeclareTask(A_TASK);
	DeclareTask(B_TASK);
	DeclareTask(SAFTEY_TASK);
	DeclareTask(DISPLAY_TASK);

	//declare events
	DeclareEvent(AEvent);
	DeclareEvent(BEvent);
	DeclareEvent(SafteyEvent);
	DeclareEvent(DisplayEvent);
	
	//declare alarms
	DeclareAlarm(AAlarm100msec);
	DeclareAlarm(BAlarm100msec);
	DeclareAlarm(SafteyAlarm100msec);
	DeclareAlarm(DisplayAlarm400msec);

	//declare counter
	DeclareCounter(SysTimerCnt);
	
	//declare shared variables and their resources resources
	DeclareResource(AQueueResource);
	DeclareResource(BQueueResource);
	DeclareResource(SafteyQueueResource);
	DeclareResource(DisplayQueueResource);
	

	//declare 
	Router router;

	// 1msec timer interrupt hook
	void user_1ms_isr_type2(void)
	{
		(void)SignalCounter(SysTimerCnt); // Alarm counter
	}
	
	// Main Task and supporting functions:
	TASK(DISPLAY_TASK)
	{		
		displayTask.init("Display", &router, DisplayQueueResource, TaskId::DispTask);

		while(1)
		{
			WaitEvent(DisplayEvent);
			ClearEvent(DisplayEvent);

			displayTask.run();
		}
	}

	//A Task
	TASK(A_TASK)
	{
		aTask.init("ATask", &router, AQueueResource, TaskId::ATask);

		while(1)
		{
			WaitEvent(AEvent);
			ClearEvent(AEvent);

			aTask.run();
		}
	}
	

	//B Task
	TASK(B_TASK)
	{
		bTask.init("BTask", &router, BQueueResource, TaskId::BTask);

		while(1)
		{
			WaitEvent(BEvent);
			ClearEvent(BEvent);

			bTask.run();
		}
		
	}
	//Saftey Task
	TASK(SAFTEY_TASK)
	{
		safteyTask.init("SafteyTask", &router, SafteyQueueResource, TaskId::SafteyTask);

		while (1)
		{
			WaitEvent(SafteyEvent);
			ClearEvent(SafteyEvent);

			safteyTask.run();
		}

	}
}



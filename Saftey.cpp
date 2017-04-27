
#include "SAFTEYTask.h"

SAFTEYTask::SAFTEYTask()
{
	lastSeqNum = 0;
	rxCount = 0;
}


S8 SAFTEYTask::run(void)
{
	//ErrorCode::Type errCode = ErrorCode::None;
	MyTask::run();

	static U8 TouchSensorStatus_old = 0;
	U8 TouchSensorStatus;

	TouchSensorStatus = ecrobot_get_touch_sensor(NXT_PORT_S1);

	if (TouchSensorStatus == 1 && TouchSensorStatus_old == 0) 
	{
		buttonPressed = 0;
	}
	else if(TouchSensorStatus ==0 && TouchSensorStatus_old ==1)
	{
		buttonPressed = 1;
	}
	else
	{	
		buttonPressed = 0;
	}
	TouchSensorStatus_old = TouchSensorStatus;


	
	
	
	DisplayStatusMsg* m = new DisplayStatusMsg(TaskId::SAFTEYTask, lastStatusSeqNum++, this->getCount(), state, errCode, lastSeqNum, rxCount);
	errCode = router->SendMessage(m);
	if (errCode != ErrorCode::None)
	{
		// what should you do if you cant send a message ?
		delete m;	// free the storage
	}

	return 0;
}


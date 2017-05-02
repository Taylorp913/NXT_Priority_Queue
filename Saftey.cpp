
#include "Saftey.h"

SAFTEYTask::SAFTEYTask()
{
	lastSeqNum = 0;
	rxCount = 0;

}


S8 SAFTEYTask::run(void)
{
	ErrorCode::Type errCode = ErrorCode::None;
	MyTask::run();

	static U8 TouchSensorStatus_old = 0;
	U8 TouchSensorStatus;

	TouchSensorStatus = ecrobot_get_touch_sensor(NXT_PORT_S1);


	//if (TouchSensorStatus == 1 && TouchSensorStatus_old == 0) 
	//{
	//	buttonPressed = 0;
	//}
	//else if(TouchSensorStatus ==0 && TouchSensorStatus_old ==1)
	//{
	//	buttonPressed = 1;
	//}
	//else
	//{	
	//	buttonPressed = 0;
	//}
	//TouchSensorStatus_old = TouchSensorStatus;
	
	
	//SAFTEYcmdMsg* m = new SAFTEYcmdMsg(TaskId::SafteyTask, TaskId::BTask, this->lastSeqNum, buttonPressed);
	//errCode = router->SendMessage(m);
	//if (errCode != ErrorCode::None)
	//{
	//	// what should you do if you cant send a message ?
	//	delete m;	// free the storage
	//}

	SAFTEYcmdMsg* n = new SAFTEYcmdMsg(TaskId::SafteyTask, TaskId::DispTask, this->lastSeqNum, TouchSensorStatus);//buttonPressed);
	errCode = router->SendMessage(n);
	if (errCode != ErrorCode::None)
	{
		// what should you do if you cant send a message ?
		delete n;	// free the storage
	}


	return 0;
} 


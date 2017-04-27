
#include "ATask.h"

ATask::ATask() 
{
	lastSeqNum = 0;
	isLastCommandComplete = true;
	rxCount = 0;
}

// This task runs to completion each time and is woken again by an OSEK alarm
S8 ATask::run(void)
{
	ErrorCode::Type errCode = ErrorCode::None;
	// call the base class
	MyTask::run();

	// check for a new responses and process them
	// drains the priority queue each time
	Message* mPtr = NULL;
	while ((mPtr = queue.dequeueMessage()) != NULL)
	{
		this->rxCount++;
		
		// process message m
		if (mPtr->type == MsgType::BReply)
		{
			BReplyMsg *reply = (BReplyMsg*)mPtr;

			// check that the reply seqNum matches the seqNum sent
			if (this->lastSeqNum == reply->seqNum)
			{
				this->isLastCommandComplete = true;
				// check that the result is as expected
				// the result is the time the command was created
				// just a fun gimic not actually relied on

				// set error code if not
			}
		}
		else
		{
			// should not be receiving any other messages
			errCode = ErrorCode::InvalidMsgReceived;
		}

		delete mPtr;
	}


	// if last message sent has been acknoledged send the next in the series	
	if (this->isLastCommandComplete)
	{
		// notice that the only time the seqNum will be zero is on rollover!
		this->lastSeqNum++;
		U32 clock = ecrobot_get_systick_ms();
		U16 val1 = (clock >> 16);
		S16 val2 = (clock & 0xFFFF);
		ACmdMsg* cmd = new ACmdMsg(TaskId::ATask, TaskId::BTask, this->lastSeqNum, val1, val2);
		ErrorCode::Type sendErr = router->SendMessage(cmd);
		if (sendErr == ErrorCode::None)
		{
			// message sent wait for completion
			this->isLastCommandComplete = false; 
		}
		else
		{
			delete cmd;	// free the storage
			errCode = (ErrorCode::Type)(errCode | ErrorCode::PQueueFull);// sendErr);
		}
	}
	// if no reply after time out value resend previous message
	// do a few times and then error out until some type of reset
	
	DisplayStatusMsg* m = new DisplayStatusMsg(TaskId::ATask, lastStatusSeqNum++, this->getCount(), state, errCode, lastSeqNum, rxCount);
	errCode = router->SendMessage(m);
	if (errCode != ErrorCode::None)
	{
		// what should you do if you cant send a message ?
		delete m;	// free the storage
	}

	return 0;
}


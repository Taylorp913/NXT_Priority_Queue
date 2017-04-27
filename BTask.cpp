
#include "BTask.h"

BTask::BTask()
{
	lastSeqNum = 0;
	rxCount = 0;
}


S8 BTask::run(void)
{
	ErrorCode::Type errCode = ErrorCode::None;
	MyTask::run();

		
	// check for a new commands and process them
	// drains the priority queue each time
	Message* mPtr = NULL;
	while ((mPtr = queue.dequeueMessage()) != NULL)
	{
		this->rxCount++;

		// process message m
		if (mPtr->type == MsgType::ACmd)
		{
			ACmdMsg *cmd = (ACmdMsg*)mPtr;

			// get the seqNum
			this->lastSeqNum = cmd->seqNum;

			// get value 1
			// get value 2
			// add them together for the result
			S32 result = cmd->value1 + cmd->value2;
			
			// create a reply message
			// use the seq num from the cmd for the reply so they can be matched
			BReplyMsg* reply = new BReplyMsg(TaskId::BTask, TaskId::ATask, this->lastSeqNum, result);
			ErrorCode::Type sendErr = router->SendMessage(reply);
			if (sendErr != ErrorCode::None)
			{
				delete cmd; // free the storage
				errCode = (ErrorCode::Type)(errCode | sendErr);
			}
		}
		else
		{
			// should not be receiving any other message types
			errCode = ErrorCode::InvalidMsgReceived;
		}

		delete mPtr; // free the storage
	}
	
	DisplayStatusMsg* m = new DisplayStatusMsg(TaskId::BTask, lastStatusSeqNum++, this->getCount(), state, errCode, lastSeqNum, rxCount);
	errCode = router->SendMessage(m);
	if (errCode != ErrorCode::None)
	{
		// what should you do if you cant send a message ?
		delete m;	// free the storage
	}

	return 0;
}


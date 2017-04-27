
#include "DisplayTask.h"
#include <Lcd.h>

ecrobot::Lcd lcd;



// 0: "Prio example---"
// 1: "ATask: <state> <cnt>"
// 2: "BTask: <state> <cnt>"
// 3: "---------------"
// 4: "---------------"
// 5: "---------------"
// 6: "LastErr: <errCode>"


S8 DisplayTask::run(void)
{
	if (state == TaskState::Init)
	{
		lcd.clearRow(0);
		lcd.cursor(0, 0);
		lcd.putf("s", "PQ example");
		lcd.cursor(0, TaskId::ATask);
		lcd.putf("s", "A: ");
		lcd.cursor(0, TaskId::BTask);
		lcd.putf("s", "B: ");
		lcd.cursor(0, TaskId::DispTask);
		lcd.putf("s", "D: ");
		lcd.cursor(0, TaskId::End);
		lcd.putf("s", "Ukn:");
	}

	// check for a new messages and process them
	// drains the priority queue each time
	Message* mPtr = NULL;
	while ((mPtr = queue.dequeueMessage()) != NULL)
	{
		static int acnt = 0;
		static int bcnt = 0;
		ErrorCode::Type err = ErrorCode::None;

		if (mPtr->type == MsgType::DisplayStatus)
		{
			DisplayStatusMsg *status = (DisplayStatusMsg*)mPtr;
			switch (status->srcId)
			{
			case TaskId::ATask:
				acnt++;
				lcd.clearRow(TaskId::ATask);
				lcd.cursor(0, TaskId::ATask);
				lcd.putf("sdsdsdsxsd", "A:", status->type, 0, ",", status->runCount, 0, ",", status->state, 0, ",x", status->errors, 2, ",", status->lastCmdSeqNum, 0);
				err = (ErrorCode::Type)(status->errors | err);
				break;
			case TaskId::BTask:
				bcnt++;
				lcd.clearRow(TaskId::BTask);
				lcd.cursor(0, TaskId::BTask);
				lcd.putf("sdsdsdsxsd", "B:", status->type, 0, ",", status->runCount, 0, ",", status->state, 0, ",x", status->errors, 2, ",", status->lastCmdSeqNum, 0);
				err = (ErrorCode::Type)(status->errors | err);
				break;
			case TaskId::DispTask:
				lcd.clearRow(TaskId::DispTask);
				lcd.cursor(0, TaskId::DispTask);
				lcd.putf("sdsdsxsd", "D:", status->type, 0, ",", status->state, 0, ",x", err, 2, ",", status->seqNum, 0);
				err = (ErrorCode::Type)(status->errors | err);
				break;
			case TaskId::Ukn:
			case TaskId::End:
			default:
				lcd.clearRow(TaskId::End);
				lcd.cursor(0, TaskId::End);
				lcd.putf("sdsdsdsxsd", "Ukn:", status->srcId, 0, ",", status->state, 0, ":", status->type, 0, ",x", err, 2, ",", status->seqNum, 0);
				err = (ErrorCode::Type)(status->errors | err);
				break;
			}
		}
		else
		{
			// if it's not a message we handle set an error and toss the message
			// proper handling would be to send a NAK (negative acknowldegment back to the sender)
			err = ErrorCode::InvalidMsgReceived;


			lcd.clearRow(TaskId::End);
			lcd.cursor(0, TaskId::End);
			lcd.putf("sdsd", "Ukn:", mPtr->srcId, 0, ":", mPtr->type, 0, ",x", err, 2);
			lcd.clearRow(TaskId::End + 1);
			lcd.cursor(0, TaskId::End + 1);
			lcd.putf("sdsdsd", "    ", mPtr->destId, 0, ", ", mPtr->size, 2, ", ", mPtr->seqNum, 3);
		}


		// save last error code
		if (err != ErrorCode::None)
			this->lastErrorCode = (ErrorCode::Type)(this->lastErrorCode | err);


		delete mPtr;	// free the storage
	}

	lcd.clearRow(6);
	lcd.cursor(0, 6);
	lcd.putf("sdsxsd", "# ", this->getCount(), 0, ", Ox", lastErrorCode, 2, ", ", state, 0);
	lcd.disp(); // update the display

	// call into base class
	// do this last so we can see the state transitions
	MyTask::run();
		
	return 0;
}


#include "Message.h"
#include <string.h>

Message::Message()
{
	this->type = MsgType::Ukn;
	this->srcId = TaskId::Ukn;
	this->destId = TaskId::Ukn;
	this->priority = MsgPriority::LOW;
	this->size = 0;
}

Message::Message(MsgType::Type type, TaskId::Type src, TaskId::Type dest, MsgPriority::Type prio, U8 seqNum)
{
	this->type = type;
	this->srcId = src;
	this->destId = dest;
	this->priority = prio;
	this->seqNum = seqNum;
	this->size = 0;
}

// assumes null terminated string <= MessageUpdate::MaxData
ACmdMsg::ACmdMsg(TaskId::Type src, TaskId::Type dest, U8 seqNum, U16 value1, S16 value2) 
	: Message(MsgType::ACmd, src, dest, MsgPriority::MED, seqNum)
{
	this->value1 = value1;
	this->value2 = value2;
}

// assumes null terminated string <= MessageUpdate::MaxData
BReplyMsg::BReplyMsg(TaskId::Type src, TaskId::Type dest, U8 seqNum, S32 result) 
	: Message(MsgType::BReply, src, dest, MsgPriority::HIGH, seqNum)
{
	this->result = result;
}

// assumes null terminated string <= MessageUpdate::MaxData
SAFTEYcmdMsg::SAFTEYcmdMsg(TaskId::Type src, TaskId::Type dest, U8 seqNum, U8 result)
	: Message(MsgType::SafteyMSG, src, dest, MsgPriority::HIGH, seqNum)
{
	this->result = result;
}

DisplayStringMsg::DisplayStringMsg(TaskId::Type src, U8 seqNum, char* msgChars, U8 numChars) 
	: Message(MsgType::DisplayString, src, TaskId::DispTask, MsgPriority::LOW, seqNum)
{
	// copy the message content to local storage
	this->numBytes = (numChars > MaxData ? MaxData : numChars);
	memcpy(this->bytes, msgChars, numBytes);
}

// assumes null terminated string <= MessageUpdate::MaxData
DisplayStringMsg::DisplayStringMsg(TaskId::Type src, U8 seqNum, char* msgChars) 
	: Message(MsgType::DisplayString, src, TaskId::DispTask, MsgPriority::LOW, seqNum)
{
	// copy the message content to local storage
	int numChars = strlen(msgChars);
	this->numBytes = (numChars > MaxData ? MaxData : numChars);
	memcpy(bytes, msgChars, numBytes);
}

// assumes null terminated string <= MessageUpdate::MaxData
DisplayStatusMsg::DisplayStatusMsg(TaskId::Type src, U8 seqNum, U16 runCount, TaskState::Type state, ErrorCode::Type errors, U8 lastCmdSeqNum, U8 rxCount)
	: Message(MsgType::DisplayStatus, src, TaskId::DispTask, MsgPriority::LOW, seqNum)
{
	this->runCount = runCount;
	this->lastCmdSeqNum = lastCmdSeqNum;
	this->rxCount = rxCount;
	this->state = state;
	this->errors = errors;
}

// assumes null terminated string <= MessageUpdate::MaxData
//SafteyCmdMsg::SafteyCmdMsg(TaskId::Type src, U8 seqNum, U16 runCount, TaskState::Type state, ErrorCode::Type errors, U8 lastCmdSeqNum, U8 pressed)
//	: Message(MsgType::DisplayStatus, src, TaskId::DispTask, MsgPriority::LOW, seqNum)
//{
//	this->runCount = runCount;
//	this->lastCmdSeqNum = lastCmdSeqNum;
//	this->pressed = pressed;
//	this->state = state;
//	this->errors = errors;
//}

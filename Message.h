#ifndef MESSAGE_H
#define MESSAGE_H


extern "C"
{
#include "kernel.h"
#include "ecrobot_interface.h"
}
#include <cassert>

// error code mask, multiple codes might be set at the same time
// Use ((error & <Code>) != 0) to check for presence
// This would be a great usecase for a class w/ overloaded operators 
// and member functions for convienient utilites
struct ErrorCode {
	typedef enum
	{
		None				= 0x00,
		InvalidMsgReceived	= 0x01,
		InvalidDestination  = 0x02,
		NullMsgReceived		= 0x04,
		PQueueFull			= 0x10
	} Type;
};

struct MsgType {
	typedef enum
	{
		Ukn				 = 0,
		ACmd			 = 1,
		BReply			 = 2,
		DisplayString	 = 3,
		DisplayStatus	 = 4,
		End				 = 5
	} Type;
};

struct TaskId {
	typedef enum
	{
		Ukn				 = 0,
		ATask			 = 1,
		BTask			 = 2,
		DispTask		 = 3,
		End				 = 4
	} Type;
};

struct MsgPriority {
	typedef enum
	{
		Ukn				 = 0,
		LOW				 = 1,
		MED				 = 2,
		HIGH			 = 3,
		End				 = 4
	} Type;
};

struct TaskState {
	typedef enum
	{
		Ukn				 = 0,
		Init			 = 1,
		Running			 = 2,
		Dead			 = 3,
		End				 = 4
	} Type;
};

class PriorityQueue; // empty declration for the friend statement

class Message
{
	friend class PriorityQueue;

public:
	Message(void);
	virtual ~Message(){};

	Message(MsgType::Type type, TaskId::Type srcId, TaskId::Type destId, MsgPriority::Type prio, U8 seqNum);

//private:
	MsgPriority::Type priority;		// MsgPriority
	MsgType::Type type;				// MsgType
	TaskId::Type destId;			// TaskId of message destination
	TaskId::Type srcId;				// TaskId of message source
	U8 size;						// msg size in bytes including header
	U8 seqNum;						// sequence number if used
};


class ACmdMsg : public Message
{
public:
	ACmdMsg(TaskId::Type src, TaskId::Type dest, U8 seqNum, U16 value1, S16 value2);

//private:
	U16 value1;
	S16 value2;

private:
	ACmdMsg(void);
};


class BReplyMsg : public Message
{
public:
	BReplyMsg(TaskId::Type src, TaskId::Type dest, U8 seqNum, S32 result);

//private:
	S32 result;

private:
	BReplyMsg(void);
};


class DisplayStringMsg : public Message
{
public:
	static const U8 MaxData = 10;
	DisplayStringMsg(TaskId::Type src, U8 seqNum, char* msgChars, U8 numChars);
	DisplayStringMsg(TaskId::Type src, U8 seqNum, char* msgChars);

//private:
	char bytes[MaxData];
	U8 numBytes;

private:
	DisplayStringMsg(void);
};

class DisplayStatusMsg : public Message
{
public:
	DisplayStatusMsg(TaskId::Type src, U8 seqNum, U16 runCount, TaskState::Type state, ErrorCode::Type errors, U8 lastCmdSeqNum, U8 rxCount);

//private:
	U16 runCount;				// task run count at time of update
	U8 rxCount;					// number of received messages
	U8 lastCmdSeqNum;			// last command seq num received or sent
	TaskState::Type state;		// task state at time of update
	ErrorCode::Type errors;		// error code mask

private:
	DisplayStatusMsg(void);
};

#endif

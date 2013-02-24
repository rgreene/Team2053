///
/// Team 2053 FIRST FRC
///


#ifndef _T7TASK_H
#include "jankyTask.h"
#include "SerialPort.h"
#include "T7.h"
#define _T7TASK_H

class T7Task : public JankyTask	{
public:
	explicit T7Task();
	virtual ~T7Task(void);
	
	virtual void Run();
	float ReturnAngle();
	float angle;
	T7 *inclinometer;
	bool getAngleRequested;
	bool initializing;
	bool dampCmdSent;
};

#endif

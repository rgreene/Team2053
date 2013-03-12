#include "T7task.h"
#include "t7.h"
#include "jankyTask.h"
#include "WPILib.h"
#include "SerialPort.h"

//Constructor
T7Task::T7Task()
{

	angle = 0.0;
	getAngleRequested = false;
	initializing = true;
	dampCmdSent = false;
	inclinometer = new T7();
}

//Destructor
T7Task::~T7Task()
{
	delete inclinometer;
}

void T7Task::Run()
{
	if(initializing && dampCmdSent)
	{
		bool received = inclinometer->ReceiveSetDampingRequest();
		if(received)
	{
			initializing = false;
			dampCmdSent = false;
		}
	}
	else if(!dampCmdSent && initializing)
	{
		inclinometer->SendSetDampingRequest(50);
		dampCmdSent = true;
	}
	else 
	if(getAngleRequested)
	{
		//work on receiving here
		//printf("checking for angle data back\n");
		angle = inclinometer->ReceiveGetAngleRequest();
		if(angle > 0.0 || angle < 0.0)
		{
			//printf("Received angle data\n");
			NetworkTable::GetTable("T7")->PutNumber("angle",angle);	
			getAngleRequested = false;					
		}
	}
	else
	{
		//work on sending here
		//printf("Sending request for angle data\n");
		inclinometer->SendGetAngleRequest();
		getAngleRequested = true;
	}
}

float T7Task::ReturnAngle()
{
	return angle;
}

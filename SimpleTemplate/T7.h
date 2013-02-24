/*----------------------------------------------------------------------------*/
/* Copyright (c) Team 2053 2013 All Rights Reserved.						  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef T7_H_
#define T7_H_

#include "SerialPort.h"
#include "WPILib.h"
#include <sstream>
#include <stdio.h>
#include <string>

/* T7 class to ease inclinometer communication */
class T7
{
public:
	SerialPort *serial;
	char *bufferIn[60];
	
	virtual void SendGetAngleRequest();
	virtual float ReceiveGetAngleRequest();
	
	virtual bool ReceiveSetDampingRequest();
	virtual void SendSetDampingRequest(int damping);
	
	/* Constructor needs a port when initializing */
	explicit T7();
	/* Remove T7 memory allocation */
	virtual ~T7();

private:
	DISALLOW_COPY_AND_ASSIGN(T7);
	virtual std::string unpack_hex(char *buffer,int offset,int size);
	virtual int returnASCII(char ch);
};

#endif
 

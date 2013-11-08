/*----------------------------------------------------------------------------*/
/* Copyright (c) Team 2053 2013 All Rights Reserved.						  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

#include "joystick.h"

/* xbox 360 controller class to ease button mapping using the joystick class */
class xboxController
{
public:
	Joystick *joystick;

	virtual bool GetBtnA();
	virtual bool GetBtnB();
	virtual bool GetBtnX();
	virtual bool GetBtnY();
	virtual bool GetLeftBumper();
	virtual bool GetRightBumper();
	virtual bool GetBackBtn();
	virtual bool GetStartBtn();
	virtual bool GetLeftAnalogBtn();
	virtual bool GetRightAnalogBtn();
	virtual bool GetLeftTrigger();
	virtual bool GetRightTrigger();

	virtual float GetRawBtnA();
	virtual float GetRawBtnB();
	virtual float GetRawBtnX();
	virtual float GetRawBtnY();
	virtual float GetRawLeftBumper();
	virtual float GetRawRightBumper();
	virtual float GetRawBackBtn();
	virtual float GetRawStartBtn();
	virtual float GetRawLeftAnalogBtn();
	virtual float GetRawRightAnalogBtn();
	virtual float GetRawTrigger();
	virtual float GetLeftAnalogX();
	virtual float GetLeftAnalogY();
	virtual float GetRightAnalogX();
	virtual float GetRightAnalogY();
	virtual float GetDPadX();
	virtual float GetDPadY();
	
	/* Constructor needs a port when initializing */
	explicit xboxController(UINT32 port);
	/* Remove joystick memory allocation */
	virtual ~xboxController();

private:
	DISALLOW_COPY_AND_ASSIGN(xboxController);
};

#endif
 

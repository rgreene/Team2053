/*----------------------------------------------------------------------------*/
/* Copyright (c) Team 2053 2013. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "xboxController.h"
#include "NetworkCommunication/UsageReporting.h"
#include "WPIErrors.h"
#include <math.h>

/**
 * Construct an instance of an xbox 360 controller.
 * 
 * @param port The port on the driver station that the joystick is plugged into.
 */
xboxController::xboxController(UINT32 port)
{
	joystick = new Joystick(port);
}

/* Remove memory allocations */
xboxController::~xboxController()
{
	delete joystick;
}

/* returns bool status on button A */
bool xboxController::GetBtnA()
{
	return((bool)joystick->GetRawButton(1));
}

/* returns float value of button A */
float xboxController::GetRawBtnA()
{
	return(joystick->GetRawButton(1));
}

/* returns bool status on button B */
bool xboxController::GetBtnB()
{
	return((bool)joystick->GetRawButton(2));
}

/* returns float value of button B */
float xboxController::GetRawBtnB()
{
	return(joystick->GetRawButton(2));
}

/* returns bool status on button X */
bool xboxController::GetBtnX()
{
	return((bool)joystick->GetRawButton(3));
}

/* returns float value of button X */
float xboxController::GetRawBtnX()
{
	return(joystick->GetRawButton(3));
}

/* returns bool status on button Y */
bool xboxController::GetBtnY()
{
	return((bool)joystick->GetRawButton(4));
}

/* returns float value of button Y */
float xboxController::GetRawBtnY()
{
	return(joystick->GetRawButton(4));
}

/* returns bool status on Left Bumper */
bool xboxController::GetLeftBumper()
{
	return((bool)joystick->GetRawButton(5));
}

/* returns float value of Left Bumper */
float xboxController::GetRawLeftBumper()
{
	return(joystick->GetRawButton(5));
}

/* returns bool status on Right Bumper */
bool xboxController::GetRightBumper()
{
	return((bool)joystick->GetRawButton(6));
}

/* returns float value of Right Bumper */
float xboxController::GetRawRightBumper()
{
	return(joystick->GetRawButton(6));
}

/* returns bool status for Back Button */
bool xboxController::GetBackBtn()
{
	return((bool)joystick->GetRawButton(7));
}

/* returns float value of the Back Button */
float xboxController::GetRawBackBtn()
{
	return(joystick->GetRawButton(7));
}

/* returns bool status for Start Button */
bool xboxController::GetStartBtn()
{
	return((bool)joystick->GetRawButton(8));
}

/* returns float value of the Start Button */
float xboxController::GetRawStartBtn()
{
	return(joystick->GetRawButton(8));
}

/* returns bool status for the Left Analog Button */
bool xboxController::GetLeftAnalogBtn()
{
	return((bool)joystick->GetRawButton(9));
}

/* returns float value of the Left Analog Button */
float xboxController::GetRawLeftAnalogBtn()
{
	return(joystick->GetRawButton(9));
}

/* returns bool status for the Right Analog Button */
bool xboxController::GetRightAnalogBtn()
{
	return((bool)joystick->GetRawButton(10));
}

/* returns float value of the Right Analog Button */
float xboxController::GetRawRightAnalogBtn()
{
	return(joystick->GetRawButton(10));
}

/* returns bool status for the Left Trigger (positive values = left trigger is dominate) */
bool xboxController::GetLeftTrigger()
{
	return(joystick->GetRawAxis(3) > 0.0 ? true : false);
}

/* returns bool status for the Right Trigger (negative values = right trigger is dominate) */
bool xboxController::GetRightTrigger()
{
	return(joystick->GetRawAxis(3) < 0.0 ? true : false);
}

/* returns float value for Triggers (shared channel) */
float xboxController::GetRawTrigger()
{
	return(joystick->GetRawAxis(3));
}

/* returns float value for Left Analog Stick on the X axis */
float xboxController::GetLeftAnalogX()
{
	return(joystick->GetRawAxis(1));
}

/* returns float value for Left Analog Stick on the Y axis */
float xboxController::GetLeftAnalogY()
{
	return(joystick->GetRawAxis(2));
}

/* returns float value for Right Analog Stick on the X axis */
float xboxController::GetRightAnalogX()
{
	return(joystick->GetRawAxis(4));
}

/* returns float value for Right Analog Stick on the Y axis */
float xboxController::GetRightAnalogY()
{
	return(joystick->GetRawAxis(5));
}

/* returns float value for D Pad on the X axis */
float xboxController::GetDPadX()
{
	return(joystick->GetRawAxis(6));
}

/* returns float value for D Pad on the Y axis */
float xboxController::GetDPadY()
{
	return(joystick->GetRawAxis(7));
}



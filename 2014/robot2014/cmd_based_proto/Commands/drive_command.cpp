// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "drive_command.h"

float xAxis;
float yAxis;
float strafeAxis;

drive_command::drive_command() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain1);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void drive_command::Initialize() {
	xAxis = 0;
	yAxis = 0;
	strafeAxis = 0;
}
// Called repeatedly when this Command is scheduled to run
void drive_command::Execute() {
	
	if(Robot::oi->getJoystick1()->GetRawAxis(1)< 0.20 &&
	Robot::oi->getJoystick1()->GetRawAxis(1)> -0.20)
	{
		xAxis = 0;
	}else
	{
		xAxis = Robot::oi->getJoystick1()->GetRawAxis(1);
		
	}
	if(Robot::oi->getJoystick1()->GetRawAxis(4)< 0.20 &&
	Robot::oi->getJoystick1()->GetRawAxis(4)> -0.20){
		yAxis = 0;
	}else
	{
		yAxis = Robot::oi->getJoystick1()->GetRawAxis(4);
	}
	if(Robot::oi->getJoystick1()->GetRawAxis(2)< 0.20 &&
	Robot::oi->getJoystick1()->GetRawAxis(2) > -0.20){
		strafeAxis = 0;
	}else
	{
		strafeAxis = Robot::oi->getJoystick1()->GetRawAxis(2);
		
	}
	
	if(Robot::oi->getJoystick1()->GetRawButton(14))
	{
		xAxis = xAxis/2;
		yAxis = yAxis/2;
		strafeAxis = strafeAxis/2;
	}
	
	
	Robot::driveTrain1->MechDrive(yAxis 
								,-strafeAxis
								,xAxis
								);
}
// Make this return true when this Command no longer needs to run execute()
bool drive_command::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void drive_command::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void drive_command::Interrupted() {
}
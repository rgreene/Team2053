#include "DriveForwardcommand.h"
#include "../RobotMap.h"

DriveForwardcommand::DriveForwardcommand(double time) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::driveTrain1);
	SetTimeout(time);
}

// Called just before this Command runs the first time
void DriveForwardcommand::Initialize() {
	RobotMap::driveTrainRobotDrive41->SetSafetyEnabled(false);
	printf("Drive forward Command started\n");
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardcommand::Execute() {
	//printf("Drive forward Command running:");
	
	  
		Robot::driveTrain1->MechDrive(0,0.4,0);
	//printf("here");
	}



// Make this return true when this Command no longer needs to run execute()
bool DriveForwardcommand::IsFinished() {

	return IsTimedOut();
}

// Called once after isFinished returns true
void DriveForwardcommand::End() {
	printf("Drive forward command has ended");
	Robot::driveTrain1->MechDrive(0,0,0);
	RobotMap::driveTrainRobotDrive41->SetSafetyEnabled(true);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardcommand::Interrupted() {
	End();
}

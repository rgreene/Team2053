#include "DriveForwardAuto.h"

DriveForwardAuto::DriveForwardAuto(float time,float speed) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::driveTrain1);
	SetTimeout(time);
	driveSpeed = speed;
}

// Called just before this Command runs the first time
void DriveForwardAuto::Initialize() {
	RobotMap::driveTrainRobotDrive41->SetSafetyEnabled(false);
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardAuto::Execute() {
	//printf("Drive forward Command running:");
		Robot::driveTrain1->MechDrive(0,driveSpeed,0);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardAuto::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void DriveForwardAuto::End() {
	RobotMap::driveTrainRobotDrive41->SetSafetyEnabled(true);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardAuto::Interrupted() {
}

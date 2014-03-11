#include "FeederMotorCommand.h"



FeederMotorCommand::FeederMotorCommand(float Speed) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::feederArm);
	speed = Speed;
}

// Called just before this Command runs the first time
void FeederMotorCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void FeederMotorCommand::Execute() {
	Robot::feederArm->SetFeederMotor(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool FeederMotorCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void FeederMotorCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FeederMotorCommand::Interrupted() {
}

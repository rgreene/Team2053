#include "LightOnOffCommands.h"

LightOnOffCommands::LightOnOffCommands() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void LightOnOffCommands::Initialize() {
	Robot::LightRingRelay->Set(Relay::kOn);
}

// Called repeatedly when this Command is scheduled to run
void LightOnOffCommands::Execute() {
	
	//if (Robot::LightRingRelay->Get() == Relay::kOff){
		

	//}
}

// Make this return true when this Command no longer needs to run execute()
bool LightOnOffCommands::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void LightOnOffCommands::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LightOnOffCommands::Interrupted() {
}

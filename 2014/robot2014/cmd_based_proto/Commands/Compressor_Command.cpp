#include "Compressor_Command.h"

Compressor_Command::Compressor_Command() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::pneumatics);
}

// Called just before this Command runs the first time
void Compressor_Command::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void Compressor_Command::Execute() {
	Robot::pneumatics->StartCompressor();
	printf("Starting Compressor\n");
}

// Make this return true when this Command no longer needs to run execute()
bool Compressor_Command::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void Compressor_Command::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Compressor_Command::Interrupted() {
}

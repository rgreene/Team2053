#include "AutonomousCommand.h"
#include "DriveForwardcommand.h"

AutonomousCommand::AutonomousCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::driveTrain1);
}

// Called just before this Command runs the first time
void AutonomousCommand::Initialize() {
	Scheduler::GetInstance()->AddCommand(new DriveForwardcommand(60.0));
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void AutonomousCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousCommand::Interrupted() {
}

#include "ALauncher_Command.h"
#include "..\Robot.h"

Timer* endTimer = 0;
bool direction = false;
bool started = false;

ALauncher_Command::ALauncher_Command(bool dir) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::pneumatics);
	direction = dir;
}

// Called just before this Command runs the first time
void ALauncher_Command::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ALauncher_Command::Execute() {
		endTimer->Start();
		
		if(!direction)
			Robot::pneumatics->ExtendArm();
		else
			Robot::pneumatics->RetractArm();
}

// Make this return true when this Command no longer needs to run execute()
bool ALauncher_Command::IsFinished() {
		return true;
}

// Called once after isFinished returns true
void ALauncher_Command::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ALauncher_Command::Interrupted() {
}

#include "ArmLauncherCommand.h"

ArmLauncherCommand::ArmLauncherCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::pneumatics);
	aTimer = new Timer();
}

// Called just before this Command runs the first time
void ArmLauncherCommand::Initialize() {
	aTimer->Reset();
	aTimer->Start();
	isDone = false;
}

// Called repeatedly when this Command is scheduled to run
void ArmLauncherCommand::Execute() {
	if(Robot::pneumatics->GetPressurePsi()<55.0&&aTimer->Get()>=2.5)
		Robot::pneumatics->RetractArm();
	else if(aTimer->Get()>=1.6)
		Robot::pneumatics->OpenLatch();
	else if(aTimer->Get()>=0.6)
		Robot::pneumatics->ExtendArm();
	else
		Robot::pneumatics->CloseLatch();
}

// Make this return true when this Command no longer needs to run execute()
bool ArmLauncherCommand::IsFinished() {
	return isDone;
}

// Called once after isFinished returns true
void ArmLauncherCommand::End() {
	aTimer->~Timer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmLauncherCommand::Interrupted() {
	aTimer->Stop();
	aTimer->Reset();
	isDone = true;
}

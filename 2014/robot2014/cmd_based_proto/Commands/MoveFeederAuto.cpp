#include "MoveFeederAuto.h"

MoveFeederAuto::MoveFeederAuto() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::feederArm);
	rTimer = new Timer();
}

// Called just before this Command runs the first time
void MoveFeederAuto::Initialize() {
	rTimer->Reset();
	rTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void MoveFeederAuto::Execute() {
	currentTime = rTimer->Get();
	if(currentTime < 0.3)
		Robot::feederArm->SetFeeder(0.4);
	else if(currentTime < 1)
		Robot::feederArm->SetFeeder(0.2);
	else
		Robot::feederArm->StopFeederArm();	
		isDone = true;
}

// Make this return true when this Command no longer needs to run execute()
bool MoveFeederAuto::IsFinished() {
	return isDone;
}

// Called once after isFinished returns true
void MoveFeederAuto::End() {
	rTimer->Stop();
	rTimer->Reset();
	rTimer->~Timer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveFeederAuto::Interrupted() {
}

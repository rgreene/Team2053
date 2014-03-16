#include "PassCommand.h"

bool fired;

PassCommand::PassCommand(float fPr) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::pneumatics);
	rTimer = new Timer();
	firePressure = fPr;
}

// Called just before this Command runs the first time
void PassCommand::Initialize() {
	isDone = false;
	fired = false;
	rTimer->Reset();
	//rTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void PassCommand::Execute() {
	if(Robot::pneumatics->GetPressurePsi()<=firePressure&&!fired){
		Robot::pneumatics->OpenLatch();
		Robot::pneumatics->RetractArm();
	}
	else if(rTimer->Get()>=2.0)
	{
		isDone = true;
		Robot::pneumatics->ExtendArm();
	}
	else{
		fired = true;
		Robot::pneumatics->CloseLatch();
		Robot::pneumatics->RetractArm();
		rTimer->Start();
	}
	//printf("Timer: %f",rTimer->Get());

}

// Make this return true when this Command no longer needs to run execute()
bool PassCommand::IsFinished() {

	return isDone;
}

// Called once after isFinished returns true
void PassCommand::End() {
	//Robot::pneumatics->ExtendArm();
	rTimer->Stop();
	rTimer->Reset();
	fired = false;
	isDone = false;
	rTimer->~Timer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PassCommand::Interrupted() {
}

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
	
}

// Called repeatedly when this Command is scheduled to run
void PassCommand::Execute() {
	    rTimer->Start();
	    Robot::pneumatics->RetractArm();
		Robot::pneumatics->OpenLatch();
	
   
	if(rTimer->Get()>= 0.2)
	{
		isDone = true;
		Robot::pneumatics->ExtendArm();
	}
	else{
		fired = true;
		initTime = rTimer->Get();
		Robot::pneumatics->CloseLatch();
		while(rTimer->Get() < initTime + 0.2){
		  Robot::pneumatics->RetractArm();
		}
		
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

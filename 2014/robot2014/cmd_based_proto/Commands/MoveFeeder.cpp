#include "MoveFeeder.h"

//enum feederMode {kTopLimit,kLowerLimit,kRaise,kLower}

MoveFeeder::MoveFeeder(int mode) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::feederArm);
	currMode = mode;
	isDone = false;
	rTimer = new Timer();
	
}

// Called just before this Command runs the first time
void MoveFeeder::Initialize() {
	rTimer->Reset();
	rTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void MoveFeeder::Execute() {
	switch(currMode)
	{
	case 0:
		isDone = Robot::feederArm->MaxFeederArm();
	break;
	case 1:
		isDone = Robot::feederArm->MinFeederArm();	
	break;
	case 2:
		Robot::feederArm->RaiseFeederArm();
		//printf("Raising Feeder Arm");
		isDone = false;
	break;
	case 3:
		//Slowly Ramp up lowering speed'
		Robot::feederArm->LowerFeederArm();
		//printf("Lowering Feeder Arm");
		//Robot::feederArm->SetFeeder(0.1);
//		if(rTimer->Get()>=0.1)
//			Robot::feederArm->SetFeeder(0.3);
//		else
//			Robot::feederArm->SetFeeder(rTimer->Get()*);	
		isDone = false;
	break;
	case 4:
		Robot::feederArm->StopFeederArm();
		//printf("Stoping Feeder Arm");
		isDone = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveFeeder::IsFinished() {
	return isDone;
}

// Called once after isFinished returns true
void MoveFeeder::End() {
	Robot::feederArm->StopFeederArm();
	rTimer->Stop();
	rTimer->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveFeeder::Interrupted() {
	isDone = true;
}

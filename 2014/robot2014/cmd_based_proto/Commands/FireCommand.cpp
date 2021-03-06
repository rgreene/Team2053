#include "FireCommand.h"

FireCommand::FireCommand(float fPr) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::pneumatics);
	rTimer = new Timer();
	firePressure = fPr;
}

// Called just before this Command runs the first time
void FireCommand::Initialize() {
	isDone = false;
	isFired = false;
	isFirst = true;
	rTimer->Reset();
	//rTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void FireCommand::Execute() {
	if(isFirst)
	{
		isFirst = false;
		isFired = false;
		rTimer->Reset();
		rTimer->Start();
		isDone = false;
	}
	
	
	fireTime = rTimer->Get();
	
	if(isFired == false)
	{
		Robot::pneumatics->ExtendArm();
		if(Robot::pneumatics->GetPressurePsi() > firePressure)
			Robot::pneumatics->OpenGateLatch();
		isFired = true;
		isDone = false;
	}
	else
	{
		if(fireTime<0.2)//Wait for arm to extend
		{
			Robot::pneumatics->ExtendArm();
			Robot::pneumatics->OpenGateLatch();
			isFired = true;
			isDone = false;
		}
		else if(fireTime<2.5)//Retract the arm
		{
			Robot::pneumatics->RetractArm();
			Robot::pneumatics->OpenGateLatch();
			isFired = true;
			isDone = false;
		}
		else if(fireTime<3.0)//Close the latch
		{
			Robot::pneumatics->RetractArm();
			Robot::pneumatics->CloseGateLatch();
			isFired = true;
			isDone = false;
		}
		else
		{
			Robot::pneumatics->ExtendArm();
			Robot::pneumatics->CloseGateLatch();
			isFired = true;
			isDone = true;
		}
	}
	
	
}

// Make this return true when this Command no longer needs to run execute()
bool FireCommand::IsFinished() {

	return isDone;
}

// Called once after isFinished returns true
void FireCommand::End() {
	//Robot::pneumatics->ExtendArm();
	rTimer->Stop();
	rTimer->Reset();
	isFired = false;
	isDone = false;
	isFirst = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireCommand::Interrupted() {
	isDone = true;
}

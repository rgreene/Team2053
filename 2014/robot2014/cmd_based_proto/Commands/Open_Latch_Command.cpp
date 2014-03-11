#include "Open_Latch_Command.h"

Open_Latch_Command::Open_Latch_Command() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::pneumatics);
	endTimer = new Timer();
}

// Called just before this Command runs the first time
void Open_Latch_Command::Initialize() {
//	endTimer->Reset();
//	if(Robot::pneumatics->GetPressurePsi()>50.0)
//	{
//		endTimer->Start();
//	}
}

// Called repeatedly when this Command is scheduled to run
void Open_Latch_Command::Execute() {
//	if(Robot::pneumatics->GetPressurePsi()>50.0)
//	{
//		endTimer->Start();
//		printf("Opening Latch\n");
		Robot::pneumatics->OpenLatch();
//	}
}

// Make this return true when this Command no longer needs to run execute()
bool Open_Latch_Command::IsFinished() {
//	if(endTimer->Get()>=0.2)
//		return true;
//	else
		return false;
}

// Called once after isFinished returns true
void Open_Latch_Command::End() {
//
	endTimer->Stop();
	endTimer->~Timer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Open_Latch_Command::Interrupted() {
}

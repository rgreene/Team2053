#include "FeederArm.h"
#include "../Robotmap.h"



FeederArm::FeederArm() : Subsystem("FeederArm") {
	feederJag = RobotMap::FeederJag;
	feederMotorJag = RobotMap::FeederMotorJag;
}
    
void FeederArm::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
void FeederArm::StopFeederArm(){
	feederJag->Set(0.0);
}
void FeederArm::RaiseFeederArm(){
	//should be 1
	feederJag->Set(-0.8);
	printf("Raising Arm\n");
}

void FeederArm::LowerFeederArm(){
	printf("Lowering Arm\n");
	feederJag->Set(0.25);
}

bool FeederArm::MaxFeederArm(){
	if(feederJag->GetReverseLimitOK())
	{
		feederJag->Set(0.1);
		return false;
	}
	else
		return true;
}

bool FeederArm::MinFeederArm(){
	if(feederJag->GetForwardLimitOK())
	{
		feederJag->Set(0.1);
		return false;
	}
	else
		return true;
}
void FeederArm::SetFeeder(float volt)
{
	printf("Feeder Arm set to: %f\n",volt);
	feederJag->Set(volt);
}

void FeederArm::SetFeederMotor(float volt)
{
	feederMotorJag->Set(volt);
}

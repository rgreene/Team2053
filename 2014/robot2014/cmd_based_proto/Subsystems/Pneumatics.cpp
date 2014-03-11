#include "Pneumatics.h"
#include "../Robotmap.h"
#include "../Commands/Compressor_Command.h"
#include "../Commands/ArmLauncherCommand.h"
#include "../Commands/IdleCatapultGroup.h"



Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
	catapultA = RobotMap::CatapultA;
	catapultB = RobotMap::CatapultB;
	
	LiveWindow::GetInstance()->AddActuator("pneumatics","pneumatics",catapultA);
	LiveWindow::GetInstance()->AddActuator("pneumatics","pneumatics",catapultB);
	
	catapultLatchA = RobotMap::CatapultLatchA;
	catapultLatchB = RobotMap::CatapultLatchB;
	LiveWindow::GetInstance()->AddActuator("pneumatics","pneumatics",catapultLatchA);
	LiveWindow::GetInstance()->AddActuator("pneumatics","pneumatics",catapultLatchB);
	pressureSensor = RobotMap::PressureSensor;
	
	RobotCompressor = RobotMap::PneumaticsRobotCompressor;
}
    
void Pneumatics::InitDefaultCommand() {
	//Starting compressor creates its own task that does this
	//Run compressor if not doing anything else
	//SetDefaultCommand(new IdleCatapultGroup());
	SetDefaultCommand(new ArmLauncherCommand());
}

void Pneumatics::StartCompressor()
{
	RobotCompressor->Start();
}
void Pneumatics::CloseLatch()
{
	catapultLatchA->Set(true);
	catapultLatchB->Set(false);
}
void Pneumatics::OpenLatch()
{
	catapultLatchA->Set(false);
	catapultLatchB->Set(true);
}
void Pneumatics::ExtendArm()
{
	catapultA->Set(true);
	catapultB->Set(false);
}
void Pneumatics::RetractArm()
{
	catapultA->Set(false);
	catapultB->Set(true);
}
float Pneumatics::GetPressureRaw()
{
	return pressureSensor->GetVoltage();
}
float Pneumatics::GetPressurePsi()
{
	//145.0377 is 1 MPa in psi. To get the pressure we divide the
	//pressure sensors voltage by 5(the max voltage the sensor returns) and multiply it by
	//145.0377(The max psi the sensor is rate for)
	return (GetPressureRaw()-1)/4.0*(145.0377);
}
bool Pneumatics::GetHullSensor()
{
//	if(hullSensor1->Get()||hullSensor2->Get())// || hullSensor2->Get())
//		return true;
//	else
		return false;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

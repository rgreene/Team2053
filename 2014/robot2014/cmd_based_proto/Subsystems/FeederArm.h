#ifndef FEEDERARM_H
#define FEEDERARM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class FeederArm: public Subsystem {
private:
	CANJaguar* feederJag;
	CANJaguar* feederMotorJag;
public:
	FeederArm();
	void InitDefaultCommand();
	void StopFeederArm();
	void RaiseFeederArm();
	void LowerFeederArm();
	bool MaxFeederArm();
	bool MinFeederArm();
	void SetFeeder(float);
	void SetFeederMotor(float);
};

#endif

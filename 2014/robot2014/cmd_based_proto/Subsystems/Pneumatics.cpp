#include "Pneumatics.h"
#include "../Robotmap.h"
#include "../Commands/Compressor_Command.h"

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
	BandPullerA = RobotMap::PneumaticsBandPullerA;
	BandPullerB = RobotMap::PneumaticsBandPullerB;
	BandLatchA = RobotMap::PneumaticsBandLatchA;
	BandLatchB = RobotMap::PneumaticsBandLatchB;
	
	RobotCompressor = RobotMap::PneumaticsRobotCompressor;
}
    
void Pneumatics::InitDefaultCommand() {
	//Starting compressor creates its own task that does this
	//Run compressor if not doing anything else
	//SetDefaultCommand(new Compressor_Command());
}

void Pneumatics::StartCompressor()
{
	RobotCompressor->Start();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

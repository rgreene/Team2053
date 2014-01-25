#ifndef PNEUMATICS_H
#define PNEUMATICS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Proggrammer
 */
class Pneumatics: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Pneumatics();
	//Solenoids
	Solenoid* BandPullerA;
	Solenoid* BandPullerB;
	Solenoid* BandLatchA;
	Solenoid* BandLatchB;
	//Compressors
	Compressor* RobotCompressor;
	void InitDefaultCommand();
	void StartCompressor();
};

#endif

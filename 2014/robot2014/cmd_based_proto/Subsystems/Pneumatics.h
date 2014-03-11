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
	Solenoid* catapultA;
	Solenoid* catapultB;
	Solenoid* catapultLatchA;
	Solenoid* catapultLatchB;
	//Compressors
	Compressor* RobotCompressor;
	AnalogChannel* pressureSensor;
	
	DigitalInput* hullSensor1;
	DigitalInput* hullSensor2;
	
	void InitDefaultCommand();
	void StartCompressor();
	void OpenLatch();
	void CloseLatch();
	void ExtendArm();
	void RetractArm();
	float GetPressureRaw();
	float GetPressurePsi();
	bool GetHullSensor();
};

#endif

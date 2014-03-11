#ifndef DRIVEFORWARDAUTO_H
#define DRIVEFORWARDAUTO_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class DriveForwardAuto: public Command {
public:
	DriveForwardAuto(float,float);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	float driveSpeed;
};

#endif

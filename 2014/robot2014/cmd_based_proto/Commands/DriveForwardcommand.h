#ifndef DRIVEFORWARDCOMMAND_H
#define DRIVEFORWARDCOMMAND_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class DriveForwardcommand: public Command {
public:
	DriveForwardcommand(double);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	float driveTime;
	bool isDone;
};

#endif

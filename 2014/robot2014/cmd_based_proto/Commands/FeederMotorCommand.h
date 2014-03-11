#ifndef FEEDERMOTORCOMMAND_H
#define FEEDERMOTORCOMMAND_H

#include "Commands\Subsystem.h"
#include "..\Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class FeederMotorCommand: public Command {
public:
	FeederMotorCommand(float);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	float speed;
};

#endif

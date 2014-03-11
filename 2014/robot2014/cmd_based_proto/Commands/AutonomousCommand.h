#ifndef AUTONOMOUSCOMMAND_H
#define AUTONOMOUSCOMMAND_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class AutonomousCommand: public Command {
public:
	AutonomousCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef ALAUNCHER_COMMAND_H
#define ALAUNCHER_COMMAND_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class ALauncher_Command: public Command {
public:
	ALauncher_Command(bool);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	bool direction;
};

#endif

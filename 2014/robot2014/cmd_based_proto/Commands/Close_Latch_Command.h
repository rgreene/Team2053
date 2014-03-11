#ifndef CLOSE_LATCH_COMMAND_H
#define CLOSE_LATCH_COMMAND_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class Close_Latch_Command: public Command {
public:
	Close_Latch_Command();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	Timer* endTimer;
};

#endif

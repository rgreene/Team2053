#ifndef OPEN_LATCH_COMMAND_H
#define OPEN_LATCH_COMMAND_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class Open_Latch_Command: public Command {
public:
	Open_Latch_Command();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	Timer* endTimer;
};

#endif

#ifndef LIGHTONOFFCOMMANDS_H
#define LIGHTONOFFCOMMANDS_H
#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class LightOnOffCommands: public Command {
public:
	LightOnOffCommands();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

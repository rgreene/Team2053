#ifndef COMPRESSOR_COMMAND_H
#define COMPRESSOR_COMMAND_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class Compressor_Command: public Command {
public:
	Compressor_Command();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

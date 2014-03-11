#ifndef PASSCOMMAND_H
#define PASSCOMMAND_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class PassCommand: public Command {
public:
	PassCommand(float fPr);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	bool isDone;
	Timer* rTimer;
	float firePressure;
	float initTime;
};

#endif

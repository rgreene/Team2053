#ifndef PASSCOMMAND_H
#define PASSCOMMAND_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class FireCommand: public Command {
public:
	FireCommand(float fPr);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	bool isDone;
	Timer* rTimer;
	float firePressure;
	bool isFirst;
	bool isFired;
};

#endif

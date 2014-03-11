#ifndef MOVEFEEDERAUTO_H
#define MOVEFEEDERAUTO_H

#include "../Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class MoveFeederAuto: public Command{
public:
	MoveFeederAuto();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	double currentTime;
	Timer* rTimer;
	bool isDone;
};

#endif

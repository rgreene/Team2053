#ifndef MOVEFEEDER_H
#define MOVEFEEDER_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class MoveFeeder: public Command {
public:
	MoveFeeder(int);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
//	static typedef enum {kBottomLimit, kTopLimit,kRaise, kLower} feederMode;
private:
	int currMode;
	bool isDone;
	Timer* rTimer;
}; 

#endif

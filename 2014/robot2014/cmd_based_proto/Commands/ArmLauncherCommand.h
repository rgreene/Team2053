#ifndef ARMLAUNCHERCOMMAND_H
#define ARMLAUNCHERCOMMAND_H

#include "..\Robot.h"

/**
 *
 *
 * @author Proggrammer
 */
class ArmLauncherCommand: public Command {
public:
	ArmLauncherCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	Timer* aTimer;
	bool isDone;
};

#endif

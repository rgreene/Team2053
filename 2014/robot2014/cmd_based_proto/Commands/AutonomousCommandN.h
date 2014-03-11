#ifndef AUTONOMUSCOMMAND_H
#define AUTONOMUSCOMMAND_H


#include "../Robot.h"


/**
 *
 *
 * @author Proggrammer
 */
class AutonomousCommandN: public Command {
	
	struct Scores {
			double rectangularity;
			double aspectRatioVertical;
			double aspectRatioHorizontal;
		};
		
		struct TargetReport {
			int verticalIndex;
			int horizontalIndex;
			bool Hot;
			double totalScore;
			double leftScore;
			double rightScore;
			double tapeWidthScore;
			double verticalScore;
		};
	
public:
	AutonomousCommandN();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	float driveTime;
	float driveSpeed;
	bool isDone;
	bool takePicture;
	bool isHot;
	Timer *aTimer;
	int state;
	
	virtual double computeDistance(BinaryImage*, ParticleAnalysisReport*);
	virtual double scoreAspectRatio(BinaryImage*, ParticleAnalysisReport*, bool);
	virtual bool scoreCompare(Scores, bool);
	virtual double scoreRectangularity(ParticleAnalysisReport*);
	virtual double ratioToScore(double);
	virtual bool hotOrNot(TargetReport);
};

#endif

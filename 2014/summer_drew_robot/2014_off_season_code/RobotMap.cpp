// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
CANJaguar* RobotMap::driveTrainFront_Left = NULL;
CANJaguar* RobotMap::driveTrainFront_Right = NULL;
CANJaguar* RobotMap::driveTrainBack_Left = NULL;
CANJaguar* RobotMap::driveTrainBack_Right = NULL;
RobotDrive* RobotMap::driveTrainRobotDrive41 = NULL;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();

	driveTrainFront_Left = new CANJaguar(2);
	
	
	driveTrainFront_Right = new CANJaguar(3);
	
	
	driveTrainBack_Left = new CANJaguar(4);
	
	
	driveTrainBack_Right = new CANJaguar(5);
	
	
	driveTrainRobotDrive41 = new RobotDrive(driveTrainFront_Left, driveTrainBack_Left,
              driveTrainFront_Right, driveTrainBack_Right);
	
	driveTrainRobotDrive41->SetSafetyEnabled(true);
        driveTrainRobotDrive41->SetExpiration(0.1);
        driveTrainRobotDrive41->SetSensitivity(0.5);
        driveTrainRobotDrive41->SetMaxOutput(1.0);
        driveTrainRobotDrive41->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
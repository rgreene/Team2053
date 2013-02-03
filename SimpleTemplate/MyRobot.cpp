#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "SmartDashboard.h"
#include "DriverStation.h"
#include <string>
#include "math.h"
#include "xboxController.h"

/*
 * Tigertronics 2053, 2013
 */ 

class RobotDemo : public SimpleRobot
{

	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;		// robot will use Jags for drive motors
	
	// Def CAN connections
	CANJaguar *JagLR; // wheel drive Left Right
	CANJaguar *JagLF; // wheel drive Left Front
	CANJaguar *JagRR; // wheel drive Right Right
	CANJaguar *JagRF; // wheel drive Right Front
	
	//Variables to get values from joysticks
	float stick_x[2];
	float stick_y[2];
	float deadband;
	bool setSticks;

	// Declare a variable for the xbox controller
	xboxController *xbox;
	
	static const int NUxbox_BUTTONS = 16;
	bool xboxButtonState[(NUxbox_BUTTONS+1)];
	bool m_leftStickButtonState[(NUxbox_BUTTONS+1)];	

public:
	RobotDemo(void)
	{
		NetworkTable::GetTable("robotMovement")->PutNumber("angle",0.0);
		NetworkTable::GetTable("robotMovement")->PutNumber("currAngle",10.0);
		NetworkTable::GetTable("robotMovement")->PutBoolean("tableRead",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("tableUpdated",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("tableInUse",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("adjustEnabled",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("forward",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("back",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("left",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("right",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("strafeLeft",false);
		NetworkTable::GetTable("robotMovement")->PutBoolean("strafeRight",false);
		NetworkTable::GetTable("robotMovement")->PutString("currMode","None");

		setSticks = false;
		xbox = new xboxController(1);

		JagLF = new CANJaguar(2); //left rear 4      5
		JagRR = new CANJaguar(3); // right front 6   3
		
		JagLR = new CANJaguar(5); //left front 11    2
		JagRF = new CANJaguar(4); // right rear 2    4

		// Create a robot using standard right/left Jag controllers
		m_robotDrive = new RobotDrive(JagLF,JagLR,JagRF,JagRR);

		// Iterate over all the buttons on each joystick, setting state to false for each
		UINT8 buttonNum = 1;						// start counting buttons at button 1
		for (buttonNum = 1; buttonNum <= NUxbox_BUTTONS; buttonNum++) {
			xboxButtonState[buttonNum] = false;
			m_leftStickButtonState[buttonNum] = false;
		}
		
		//set joystick deadband
		deadband=0.20;

		m_robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
		m_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor,false);
		m_robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor,true );
		m_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor,false);
		
		m_robotDrive->SetSafetyEnabled(false);//NEED THIS!!

	}

	void Autonomous(void)
	{
		NetworkTable::GetTable("robotMovement")->PutString("currMode","Autonomous");
		printf("Robot is now in: Autonomous mode.\n");
		while(IsAutonomous() && IsEnabled()) {
			if(NetworkTable::GetTable("robotMovement")->GetBoolean("adjustEnabled")) {
				if(!NetworkTable::GetTable("robotMovement")->GetBoolean("tableRead")) {
					printf("Adjustment authorized!\n");
				}
				handleRobotAdjustment();
				fireFrisbee();
			}
			Wait(0.05);
		}
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		NetworkTable::GetTable("robotMovement")->PutString("currMode","Teleoperated");		
		printf("Robot is now in: Teleoperated mode.\n");
		while (IsOperatorControl() && IsEnabled())
		{
			if (xbox->GetBtnA())
			{
				// Seek and destroy
				if(!NetworkTable::GetTable("robotMovement")->GetBoolean("tableRead")) 
				{
					printf("Adjustment authorized!\n");
				}
				//handleRobotAdjustment();
				
				if((NetworkTable::GetTable("robotMovement")->GetBoolean("firesln")) && 
				   (xbox->GetRightTrigger())) 
				{
					fireFrisbee();
				}
			}
			else
			{
				// FIRE!
				if (xbox->GetRightTrigger())
				{
					fireFrisbee();
				}
				
				//Get Joystick Values
				// strafe on right analog = back button
				if(xbox->GetBackBtn()) 
				{
					setSticks = true;
					NetworkTable::GetTable("xbox")->PutString("Stafe_Stick","Right");
					//printf("Right Stick is Strafe!\n");
				}
				else if(xbox->GetStartBtn()) 
				{ 
					setSticks = false;
					NetworkTable::GetTable("xbox")->PutString("Stafe_Stick","Left");
					//printf("Left Stick is Strafe!\n");				
				}
				// strafe on right analog = back button
				if(setSticks) 
				{
					stick_x[0]=xbox->GetLeftAnalogX();
					stick_y[0]=xbox->GetLeftAnalogY();
					stick_x[1]=xbox->GetRightAnalogX();
					stick_y[1]=xbox->GetRightAnalogY();
				}
				else
				{//strafe on left analog = start button
					stick_x[1]=xbox->GetLeftAnalogX();
					stick_y[1]=xbox->GetLeftAnalogY();
					stick_x[0]=xbox->GetRightAnalogX();
					stick_y[0]=xbox->GetRightAnalogY();
				}
				
				// Apply deadband to controls
				if (stick_x[0]<deadband && stick_x[0]>(-1*deadband))
					stick_x[0]=0;
				
				if (stick_y[0]<deadband && stick_y[0]>(-1*deadband))
					stick_y[0]=0;
				
				if (stick_x[1]<deadband && stick_x[1]>(-1*deadband))
					stick_x[1]=0;
				
				if (stick_y[1]<deadband && stick_y[1]>(-1*deadband))
					stick_y[1]=0;
				
				// MecanumDrive
				m_robotDrive->MecanumDrive_Cartesian(stick_x[1]  *-1,stick_y[0]  , (stick_x[0]  ), 0.00);
			}
			Wait(.01);
		}
	}
	// Checks if table isn't being used currently and has been updated
	// and then begins adjusting robot until all movements are false and 
	// curAngle == angle.  Frisbee is then fired.
	void handleRobotAdjustment() 
	{
		bool adjust = checkAdjustment();
		printf("Handling Robot Adjustment!\n");
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("tableUpdated")) 
		{
			if(!(NetworkTable::GetTable("robotMovement")->GetBoolean("tableInUse")))
			{
				// Lock table values
				printf("Table not in use, locking!\n");
				NetworkTable::GetTable("robotMovement")->PutBoolean("tableInUse",true);
				printf("Removing updated status!\n");
				NetworkTable::GetTable("robotMovement")->PutBoolean("tableUpdated",false);
				strafeLeft();
				strafeRight();
				left();
				right();
				forward();
				back();
				updateLauncherAngle();
				printf("Indicating table has been read!\n");
				NetworkTable::GetTable("robotMovement")->PutBoolean("tableRead",true);
				// Release lock on table
				printf("Releasing lock on table!\n");
				NetworkTable::GetTable("robotMovement")->PutBoolean("tableInUse",false);
				adjust = checkAdjustment();
			}
			else 
			{
			    printf("Table is locked, awaiting updates =)\n");
			}
		}
	}
	bool checkAdjustment() {
		return(NetworkTable::GetTable("robotMovement")->GetBoolean("strafeLeft") ||
			   NetworkTable::GetTable("robotMovement")->GetBoolean("strafeRight") ||
			   NetworkTable::GetTable("robotMovement")->GetBoolean("left") ||
			   NetworkTable::GetTable("robotMovement")->GetBoolean("right") ||
			   NetworkTable::GetTable("robotMovement")->GetBoolean("forward") ||
			   NetworkTable::GetTable("robotMovement")->GetBoolean("back") ||
			   (NetworkTable::GetTable("robotMovement")->GetNumber("angle") != 45.0));
	}
	void strafeLeft() 
	{
		// Strafe robot Left an incremental amount
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("strafeLeft")) 
		{
			//move a little
			m_robotDrive->MecanumDrive_Cartesian(0.5,0,0, 0.00);
			Wait(0.01);
			m_robotDrive->MecanumDrive_Cartesian(0,0,0, 0.00);
		}
	}
	
	void strafeRight() 
	{
		// Strafe robot Right an incremental amount
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("strafeRight")) 
		{
			//move a little
			m_robotDrive->MecanumDrive_Cartesian(-0.5,0,0, 0.00);
			Wait(0.01);
			m_robotDrive->MecanumDrive_Cartesian(0,0,0, 0.00);
		}
	}
	void forward() 
	{
		// Move robot Forward an incremental amount
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("forward")) 
		{			
			//move a little
			m_robotDrive->MecanumDrive_Cartesian(0,0.5,0, 0.00);
			Wait(0.01);
			m_robotDrive->MecanumDrive_Cartesian(0,0,0, 0.00);
		}
	}
	
	void back() 
	{
		// Move robot Back an incremental amount
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("back")) 
		{
			//move a little
			m_robotDrive->MecanumDrive_Cartesian(0,-0.5,0, 0.00);
			Wait(0.01);
			m_robotDrive->MecanumDrive_Cartesian(0,0,0, 0.00);
		}
	}
	void left() 
	{
		// Turn robot Left an incremental amount
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("left")) 
		{
			//move a little
			m_robotDrive->MecanumDrive_Cartesian(0,0,-0.5, 0.00);
			Wait(0.01);
			m_robotDrive->MecanumDrive_Cartesian(0,0,0, 0.00);
		}
	}
	void right() 
	{
		// Turn robot Right an incremental amount
		if(NetworkTable::GetTable("robotMovement")->GetBoolean("right")) 
		{
			//move a little
			m_robotDrive->MecanumDrive_Cartesian(0,0,0.5, 0.00);
			Wait(0.01);
			m_robotDrive->MecanumDrive_Cartesian(0,0,0, 0.00);
		}		
	}
	void updateLauncherAngle() 
	{
		double angleUpdate = NetworkTable::GetTable("robotMovement")->GetNumber("angle");
		while(angleUpdate > getCurrLauncherAngle()) 
		{
			//move launcher down
			printf("Adjusting Launcher down to proper angle, current angle: %f\n",angleUpdate);
			angleUpdate--;			
		}
		while(angleUpdate < getCurrLauncherAngle()) 
		{
			//move launcher up
			printf("Adjusting Launcher up to proper angle, current angle: %f\n",angleUpdate);
			angleUpdate++;
		}
	}
	double getCurrLauncherAngle() 
	{
		double angle = 45.0;
		return angle;
	}
	void fireFrisbee() 
	{
		printf("Frisbee(s) fired, death from below! >:D\n");
	}
	/**
	 * Runs during test mode
	 */
	void Test() 
	{
		NetworkTable::GetTable("robotMovement")->PutString("currMode","Test");
		printf("Robot is now in: Test mode.\n");
	}
};

START_ROBOT_CLASS(RobotDemo);


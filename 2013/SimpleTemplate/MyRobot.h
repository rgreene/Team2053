#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "smartdashboard/SmartDashboard.h"
#include "DriverStation.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <ios>
#include "math.h"
#include "xboxController.h"
#include "T7task.h"

/*
 * Tigertronics 2053, 2013
 */ 
enum Driving_Modes_Type {KEEP_DRIVING, FEED_DISCS, PICKUP_DISCS, AUTO_AIM, EXIT_AUTO_AIM, BAR_HANG};

class RobotDemo : public SimpleRobot
{

	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;		// robot will use Jags for drive motors
	
	CANJaguar *JagLR; // wheel drive Left Right
	CANJaguar *JagLF; // wheel drive Left Front
	CANJaguar *JagRR; // wheel drive Right Right
	CANJaguar *JagRF; // wheel drive Right Front
	
	CANJaguar *ShooterTop; // Top shooter wheels
	CANJaguar *ShooterBottom ;// Bottom shoot wheels
	
	CANJaguar *FrisbeeBelt; // Frisbee getter belt

	
	//CANJaguar *BreachLoader; //Used to place frisbe for firing.
	Servo *loaderArm; // load frisbe
	
	CANJaguar *WinchJag; // Winch control (angle)
	Timer *fireTimer;

	//Variables to get values from joysticks
	float stick_x[2];
	float stick_y[2];
	
	float topShooterOffset;
	float bottomShooterOffset;
	float deadband;
	int swapControls;
	int trigCnt;
	
	bool btnPressed;
	
	bool btnPressed_2;
	bool setLoader;
	bool getAngleRequested;
	bool setDamping;
	bool isConveyorOn;
	bool triggerOn;
	bool sweetSpot;
	
	int num;
	
	float loaderDriveVal;
	float angle;
	float Shooter_Angle_Command;

	bool Shooter_Moving_Up;
	bool Shooter_Moving_Down;
	
	bool Conveyor_is_On;
	

	UINT8 buttonNum;	// start counting buttons at button 1

	
	// Declare variables for the robot controllers
	xboxController *xbox;
	Joystick *ModeStick;
	
	
	T7Task *angleTask;
	

	static const int NUM_BUTTONS = 16;
	bool ModeStick_ButtonState[(NUM_BUTTONS+1)];	

	Driving_Modes_Type Driving_Mode;
	
	
	
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

		swapControls = 0;
        sweetSpot = false;
		topShooterOffset = 0;
		bottomShooterOffset = 0;
		
		triggerOn = false;
		btnPressed = false;

		btnPressed_2 = false;
		setLoader = false;
		loaderDriveVal = 0.0;
		trigCnt = 0;
		
		xbox = new xboxController(1);
		ModeStick = new Joystick(2);

		angleTask = new T7Task();

		JagLF = new CANJaguar(2); //left rear 4      5
		JagRR = new CANJaguar(3); // right front 6   3
		
		JagLR = new CANJaguar(5); //left front 11    2
		JagRF = new CANJaguar(4); // right rear 2    4

		ShooterTop = new CANJaguar(7,CANJaguar::kPercentVbus); // Top shooter wheels
		ShooterBottom = new CANJaguar(6,CANJaguar::kPercentVbus);// Bottom shoot wheels
		
		WinchJag = new CANJaguar(8);
		
		FrisbeeBelt = new CANJaguar(9);
		
		fireTimer = new Timer();//Timer for servo positions when shooting
		
	
		// Create a robot using standard right/left Jag controllers
		m_robotDrive = new RobotDrive(JagLF,JagLR,JagRF,JagRR);
		
		loaderArm = new Servo(1,1);

		// Iterate over all the buttons on each joystick, setting state to false for each
		for (buttonNum = 1; buttonNum <= NUM_BUTTONS; buttonNum++) 
		{
			ModeStick_ButtonState[buttonNum] = false;
		}
		
		//set joystick deadband
		deadband=0.20;

		m_robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
		m_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor,false);
		m_robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor,true );
		m_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor,false);
		
		m_robotDrive->SetSafetyEnabled(false);//NEED THIS!!
		
		isConveyorOn = false;
		getAngleRequested = false;
		setDamping = true;
		angle = 0.0;
		angleTask->Run();
		
		Driving_Mode = KEEP_DRIVING;
		Shooter_Angle_Command = 28.0;
		Shooter_Moving_Up = false;
		Shooter_Moving_Down = false;
	
		Conveyor_is_On = false;
	}

	void Autonomous(void)
	{
		NetworkTable::GetTable("robotMovement")->PutString("currMode","Autonomous\0");
		
		//printf("Robot is now in: Autonomous mode.\n");
		num = 0;
		double Shooter_Angle;
		Shooter_Angle = NetworkTable::GetTable("T7")->GetNumber("angle");
		
		while(IsAutonomous() && IsEnabled() && num < 5) 
			
		{

			Shooter_Angle = NetworkTable::GetTable("T7")->GetNumber("angle");

		
		
		    if (Shooter_Angle > 28.0 && Shooter_Angle < 29.0  )
			{
				WinchJag->Set(0.0);
				fireFrisbee(*loaderArm,*ShooterBottom,*ShooterTop,*fireTimer);
				sweetSpot = true;
			}
			
			else if(Shooter_Angle>28.0 && sweetSpot == false)
			{
					WinchJag->Set(-1.0);
			}
			else if(Shooter_Angle<29.0 && sweetSpot == false)
			{
					WinchJag->Set(1.0);
			}
			
		}
		ShooterTop->Set(0.0);
		ShooterBottom->Set(0.0);		
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	
	{
		
		sweetSpot = false;
		NetworkTable::GetTable("robotMovement")->PutString("currMode","Teleoperated\0");		
		printf("Robot is now in: Teleoperated mode.\n");

		
		while (IsOperatorControl() && IsEnabled())
		{
			angle = NetworkTable::GetTable("T7")->GetNumber("angle");
			//NetworkTable::GetTable("T7")->PutNumber("angle",angle);
			
			
			//-------------------------------------------------------------------
			// Update roboto contoller button states
			//-------------------------------------------------------------------
			
			for (buttonNum = 1; buttonNum <= NUM_BUTTONS; buttonNum++) 
			{
				ModeStick_ButtonState[buttonNum] = ModeStick->GetRawButton(buttonNum);
			}
		
			//--------------------------------------------------------------------
			// Update driving mode based on button state
			//--------------------------------------------------------------------
			     if ( ModeStick_ButtonState[1] )    ;
			else if ( ModeStick_ButtonState[2] )    ;
			else if ( ModeStick_ButtonState[3] )    ;
			else if ( ModeStick_ButtonState[4] )    ;
			else if ( ModeStick_ButtonState[5] )    ;
			else if ( ModeStick_ButtonState[6] )  Driving_Mode = FEED_DISCS  ;
			else if ( ModeStick_ButtonState[7] )  Driving_Mode = PICKUP_DISCS  ;
			else if ( ModeStick_ButtonState[8] )  Driving_Mode = AUTO_AIM  ;
			else if ( ModeStick_ButtonState[9] )  Driving_Mode = EXIT_AUTO_AIM  ;
			else if ( ModeStick_ButtonState[10] ) Driving_Mode = BAR_HANG  ;
			else if ( ModeStick_ButtonState[11] )   ;
			else if ( ModeStick_ButtonState[12] )   ;
			
			//------------------------------------------------------------------
			//  Command robot based on mode
			//------------------------------------------------------------------
			     
			switch (Driving_Mode)
			{
			  case FEED_DISCS :
			      Set_Shooter_Angle_Command( 35.0 );
			      Driving_Mode = KEEP_DRIVING;
			      break;

			  case PICKUP_DISCS :
				  Set_Shooter_Angle_Command( 53.0 );
				  Driving_Mode = KEEP_DRIVING;
			      break;

			  case AUTO_AIM :
			      ;  // get shooter angle from vision stuff
			      break;

			   case EXIT_AUTO_AIM :
			      Driving_Mode = KEEP_DRIVING;
			      break;

			   case BAR_HANG :
				   Set_Shooter_Angle_Command( 50.0 );
			      Driving_Mode = KEEP_DRIVING;
			      break;
			      
			   case KEEP_DRIVING :
			      ; // do nothing, keep going
			      break;
			}


			Control_Shooter_Angle();
			
			ManualShooterAngle();
			Turn_Conveyor_On_or_Off();
			
			controlsChangeCheck();			
						
			// -------------------------------------------------------
			// Manually fire discs using joystick trigger
			// -------------------------------------------------------
			if (ModeStick_ButtonState[1])
			{
				fireFrisbee(*loaderArm,*ShooterBottom,*ShooterTop,*fireTimer);
			}else{
				loaderArm->Servo::SetAngle(155.0); // set servo to angle
				ShooterTop->Set(0.0);
				ShooterBottom->Set(0.0);
			}
			
			// ---------------------------------------------------------
			// MecanumDrive
			//----------------------------------------------------------
			applyDeadband();	
			m_robotDrive->MecanumDrive_Cartesian(stick_x[1]  *-1,stick_y[0]  , (stick_x[0]  ), 0.00);
		}
	}

	//--------------------------------------------------------------------
	// Control the shooter angle to the commanded value closing the loop
	// with the angle from the inclinometer
	//---------------------------------------------------------------------
    void Control_Shooter_Angle()
    {
		double Shooter_Angle_LDB;
		double Shooter_Angle_UDB;

		double Shooter_Angle;
		
		
		Shooter_Angle_LDB = Shooter_Angle_Command - 0.5;
		Shooter_Angle_UDB = Shooter_Angle_Command + 0.5;
		
    	Shooter_Angle = NetworkTable::GetTable("T7")->GetNumber("angle");
	
	    if (Shooter_Angle > Shooter_Angle_LDB && 
	        Shooter_Angle < Shooter_Angle_UDB     )
		{
	    	Command_Shooter_Stop();
			sweetSpot = true;
		}
		
		else if(Shooter_Angle > Shooter_Angle_LDB && sweetSpot == false)
		{
			Command_Shooter_Down();
		}
		else if(Shooter_Angle < Shooter_Angle_UDB && sweetSpot == false)
		{
			Command_Shooter_Up();
		}
		
	}

    void Set_Shooter_Angle_Command( double new_angle_command)
    {
        sweetSpot = false;
    	Shooter_Angle_Command = new_angle_command;
    }
    
    
    void Increase_Shooter_Angle_Command()
	{
		sweetSpot = false;
        Shooter_Angle_Command = Shooter_Angle_Command + 0.5;
		if ( Shooter_Angle_Command >= 54.0 )
		   Shooter_Angle_Command = 54.0;
	
	}
   
	void Decrease_Shooter_Angle_Command()
	{
		sweetSpot = false;
		Shooter_Angle_Command = Shooter_Angle_Command - 0.5;
		if ( Shooter_Angle_Command <= 25.0 )
		   Shooter_Angle_Command = 25.0;
	}

	
	void ManualShooterAngle()
	{
		if(ModeStick_ButtonState[2])
		{
			//WinchJag->CANJaguar::Set(-1.0);
			Decrease_Shooter_Angle_Command();
		}
		else if(ModeStick_ButtonState[3])
		{
			//WinchJag->CANJaguar::Set(1.0);
			Increase_Shooter_Angle_Command();
		}		
	}
	

	void Command_Shooter_Up()
	{
		if ( !Shooter_Moving_Up )
		{
			WinchJag->CANJaguar::Set(1.0);
			Shooter_Moving_Up = true;
			Shooter_Moving_Down = false;
		}
	}
	  
	void Command_Shooter_Down()
	{
		if ( !Shooter_Moving_Down )
		{
			WinchJag->CANJaguar::Set(-1.0);
			Shooter_Moving_Up = false;
			Shooter_Moving_Down = true;
		}
	}
	
	void Command_Shooter_Stop()
	{
		WinchJag->CANJaguar::Set(0.0);
		Shooter_Moving_Up = false;
		Shooter_Moving_Down = false;
	}

	//-------------------------------------------------------
	// Turn conveyor on/off based on xbox left trigger 
	//--------------------------------------------------------


	void Turn_Conveyor_On_or_Off()
	{
	  if( xbox->GetLeftTrigger() )
	  {
	     if ( Conveyor_is_On) 
		 {
			FrisbeeBelt->Set(0.0); // turn off conveyor
			Conveyor_is_On = false;
		
		 }
		 else
		 {
			FrisbeeBelt->Set(-1.0); // turn on convery
			Conveyor_is_On = true;
		 }
	   }
	}			
		
	
	
	void applyDeadband()
	{
		// Apply deadband to controls
		if (stick_x[0]<deadband && stick_x[0]>(-1*deadband))
			stick_x[0]=0;
		if (stick_y[0]<deadband && stick_y[0]>(-1*deadband))
			stick_y[0]=0;
		if (stick_x[1]<deadband && stick_x[1]>(-1*deadband))
			stick_x[1]=0;
		if (stick_y[1]<deadband && stick_y[1]>(-1*deadband))
			stick_y[1]=0;		
	}
	
	void shooterWheelsAdjust()
	{
		if(xbox->GetBtnA())
		{
			if(xbox->GetLeftBumper())
			{
				bottomShooterOffset = bottomShooterOffset + 0.001;
			}
			if(xbox->GetRightBumper())
			{
				bottomShooterOffset = bottomShooterOffset - 0.001;					
			}
		}
		if(xbox->GetBtnB())
		{
			if(xbox->GetLeftBumper())
			{
				topShooterOffset = topShooterOffset + 0.001;
			}
			if(xbox->GetRightBumper())
			{
				topShooterOffset = topShooterOffset - 0.001;
			}
		}
		if(!xbox->GetBtnA() && !xbox->GetBtnB())
		{
			ShooterTop->Set(0.0);
			ShooterBottom->Set(0.0);
		}else if(xbox->GetBtnA() || xbox->GetBtnB())
		{
			ShooterTop->Set(-0.864+topShooterOffset);
			NetworkTable::GetTable("Shooters")->PutNumber("Top",(-0.864+topShooterOffset));
			ShooterBottom->Set(-0.864+bottomShooterOffset);
			NetworkTable::GetTable("Shooters")->PutNumber("Bottom",(-0.864+bottomShooterOffset));				
		}		
	}

	void conveyorLoader()
	{
		float TheAngle;
		static bool setAngle;
		//static bool trigger_state;
		if(xbox->GetLeftTrigger())
		{
			if(trigCnt > 1 && !triggerOn)
			{
				loaderDriveVal = 0.0;
				trigCnt = 0;
				triggerOn = true;
			}
			else if(!triggerOn)
			{
				TheAngle = NetworkTable::GetTable("T7")->GetNumber("angle");
				printf("%f\n",TheAngle);
				if (TheAngle < 53.4)
				{
					if (setAngle == false)
					{
						setAngle = true;
						WinchJag->CANJaguar::Set(1.0);
					}
				}
				else if ( TheAngle > 55.0 )
				{
					if (setAngle == false)
					{
						setAngle = true;
						WinchJag->CANJaguar::Set(-1.0);
					}
				}	
				else 
				{
				WinchJag->CANJaguar::Set(0.0);	
				trigCnt = 1;
				loaderDriveVal = -1.0;
				triggerOn = true;
				}
			}
		}
		else if(!(xbox->GetLeftTrigger()))
		{
			if(trigCnt == 1)
			{
				trigCnt = 2;
			}
			triggerOn = false;
		}
		FrisbeeBelt->Set(loaderDriveVal); // negative grabs frisbee
	}
	
	void controlsChangeCheck()
	{	
		//Get Joystick Values
		// strafe on right analog = back button
		if(xbox->GetBackBtn() && !btnPressed)
		{
			btnPressed = true;
			swapControls++;
			if(swapControls == 4)
			{
				swapControls = 0;
			}
			if(swapControls == 0)
			{
				NetworkTable::GetTable("xbox")->PutString("Stafe_Stick","Right\0");						
			}
			if(swapControls == 1)
			{
				NetworkTable::GetTable("xbox")->PutString("Stafe_Stick","Left\0");
			}
			if(swapControls == 2)
			{
				NetworkTable::GetTable("xbox")->PutString("Stafe_Stick","Left & fwd|bck\0");
			}
			if(swapControls == 3)
			{
				NetworkTable::GetTable("xbox")->PutString("Stafe_Stick","Right & fwd|bck\0");
			}
		}
		else if(!xbox->GetBackBtn() && btnPressed)
		{
			btnPressed = false;
		}

		if(swapControls == 0)
		{
			stick_x[0]=xbox->GetLeftAnalogY();
			stick_y[0]=xbox->GetLeftAnalogX();
			stick_x[1]=xbox->GetRightAnalogX();
			stick_y[1]=xbox->GetRightAnalogY();
			stick_x[0] = stick_x[0]*-1;
			stick_x[1] = stick_x[1]*-1;
			stick_y[0] = stick_y[0]*-1;
			stick_y[1] = stick_y[1]*-1;
			//printf("Right Stick is Strafe!\n");						
		}
		else if(swapControls == 1)
		{
			stick_x[1]=xbox->GetLeftAnalogX();
			stick_y[1]=xbox->GetLeftAnalogY();
			stick_x[0]=xbox->GetRightAnalogY();
			stick_y[0]=xbox->GetRightAnalogX();
			//printf("Left Stick is Strafe!\n");									
		}
		else if(swapControls == 2)
		{
			//strafe on x axis left analog stick with forward/back
			stick_x[0]=xbox->GetLeftAnalogY();  //strafe
			stick_y[0]=xbox->GetRightAnalogX();  //fwd/bck
			stick_x[1]=xbox->GetLeftAnalogX(); //turn
			stick_y[1]=xbox->GetRightAnalogY();
			
			
		}
		else if(swapControls == 3)
		{
			//strafe on x axis right analog stick with forward/back
			stick_x[1]=xbox->GetLeftAnalogY();  //strafe
			stick_y[1]=xbox->GetRightAnalogX();  //fwd/bck
			stick_x[0]=xbox->GetLeftAnalogX(); //turn
			stick_y[0]=xbox->GetRightAnalogY();
		}
	}
	
	// Checks if table isn't being used currently and has been updated
	// and then begins adjusting robot until all movements are false and 
	// Shooter_Angle == angle.  Frisbee is then fired.
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
	
	void fireFrisbee(Servo &loaderArm,CANJaguar &ShooterBottom, CANJaguar &ShooterTop,Timer &fireTimer) 
	{
		ShooterTop.Set(-0.722);
		ShooterBottom.Set(-0.591);
		//printf("Timer: %f",fireTimer.Timer::Get());
		if(fireTimer.Timer::Get()==0.0)
		{
			fireTimer.Timer::Start();
		}
        //loaderArm.SetSafetyEnabled(true);
		//loaderArm.Servo::SetAngle(0.0);
		//start top and bottom motor.
		//ShooterBottom.CANJaguar::Set(-0.6);
		//ShooterTop.CANJaguar::Set(-0.5);
		if(fireTimer.Timer::Get()>=2.5)
		{
			//loaderArm.Servo::SetAngle(180.0); // set servo to angle
			loaderArm.Servo::SetAngle(155.0); // set servo to angle
			NetworkTable::GetTable("Servo")->PutNumber("angle",145.0);
			NetworkTable::GetTable("Servo")->PutBoolean("reset",true);
			num++;
			fireTimer.Timer::Stop();
			fireTimer.Timer::Reset();
		}
		//Wait(0.5); // wait .5 second       
		//loaderArm.Servo::SetAngle(180.0); // set servo to angle
		else if(fireTimer.Timer::Get()>=2.0)
		{
			loaderArm.Servo::SetAngle(75.0); // set servo to angle
			NetworkTable::GetTable("Servo")->PutNumber("angle",75.0);
			NetworkTable::GetTable("Servo")->PutBoolean("reset",false);
		}
		//Wait(0.5); // wait .5 second 7
	}
		
	
	/**
	 * Runs during test mode
	 */
	void Test() 
	{
		NetworkTable::GetTable("robotMovement")->PutString("currMode","Test\0");
		printf("Robot is now in: Test mode.\n");
	}
};

START_ROBOT_CLASS(RobotDemo);


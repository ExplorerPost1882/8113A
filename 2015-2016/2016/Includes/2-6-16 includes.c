#include"SmartMotorLib.c";
//88888888888888888888888888888 stop motors 8888888888888888888888888888888888
void stopmotors()
{
	motor[frontRight] = 0;
	motor[backRight]  = 0;
	motor[frontLeft]  = 0;
	motor[backLeft]   = 0;
	wait1Msec(10);
}
void moverobot(int xx1, int xx2, int yy1, int duration, int automode, int gospeed)
{
	int direction;
	int delta = 35;
	if (automode==0)
	{
		motor[frontRight] = yy1 - xx2 - xx1;
		motor[backRight]  =  yy1 - xx2 + xx1;
		motor[frontLeft]  = yy1 + xx2 + xx1;
		motor[backLeft]   =  yy1 + xx2 - xx1;
		wait1Msec(duration);

	}
	//This section is for automous mode movement of the base
	if (automode==1)
	{
		if(yy1!=0)//code for movement forward or reverse.  +yy1=forward, -yy1=reverse
		{
			if (yy1>0) direction=1;
			else if (yy1<0) direction=-1;
			//writeDebugStream("yy1= %d", yy1);  // writes the current value of int 'yy1' to the debug stream
			nMotorEncoder[backLeft]  = 0;
			nMotorEncoder[backRight] = 0;
			// this while loop moves the base until the desired distance - yy1 - is achieved
			while ((abs(nMotorEncoder[backLeft]) < (abs(yy1)-30)) || (abs(nMotorEncoder[backRight])<(abs(yy1)-30)))
				//  || ((nMotorEncoder[backLeft]>yy1+200)&&(-nMotorEncoder[backRight]>yy1+200)))
			{
				if (abs(nMotorEncoder[backLeft]) == abs(nMotorEncoder[backRight]))
				{
					motor[frontRight] = gospeed*direction;
					motor[backRight]  = gospeed*direction;
					motor[frontLeft]  = gospeed*direction;
					motor[backLeft]   = gospeed*direction;
					wait1Msec(1);
				}
				//if moving forward and left leads, slow down left side
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[backRight])) && (direction==1))
				{
					motor[frontRight] = gospeed;
					motor[backRight]  = gospeed;
					motor[frontLeft]  = (gospeed-delta);
					motor[backLeft]   = (gospeed-delta);
					wait1Msec(1);
				}
				//if moving backward and left leads, slow down left side
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[backRight])) && (direction==-1))
				{
					motor[frontRight] = -gospeed;
					motor[backRight]  = -gospeed;
					motor[frontLeft]  = -(gospeed-delta);
					motor[backLeft]   = -(gospeed-delta);
					wait1Msec(1);
				}
				//if moving forward and left lags, slow down right side
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[backRight])) && (direction==1))
				{
					motor[frontRight] =  (gospeed-delta);
					motor[backRight]  =  (gospeed-delta);
					motor[frontLeft]  =  gospeed;
					motor[backLeft]   =  gospeed;
					wait1Msec(1);
				}
				//if moving backward and left lags, slow down right side
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[backRight])) && (direction==-1))
				{
					motor[frontRight] = -(gospeed-delta);
					motor[backRight]  = -(gospeed-delta);
					motor[frontLeft]  = -gospeed;
					motor[backLeft]   = -gospeed;
					wait1Msec(1);
				}
				else stopmotors();
			}
			stopmotors();
		}
		if(xx1!=0)//code for movement left or right.  +xx1=right, -xx1=left
		{
			if (xx1>0) direction=1;
			if (xx1<0) direction=-1;

			nMotorEncoder[backLeft]  = 0;
			nMotorEncoder[frontLeft] = 0;

			while (( abs(nMotorEncoder[backLeft]) < (abs(xx1)-30))&&(abs(nMotorEncoder[frontLeft]) < (abs(xx1)-30)))
				//||((abs(nMotorEncoder[backLeft]) > abs(xx1+200)) && abs(nMotorEncoder[frontLeft]) > abs(xx1+200)))
			{
				//move right equally
				if (abs(nMotorEncoder[backLeft]) == abs(nMotorEncoder[frontLeft]))
				{
					motor[frontRight] = -gospeed*direction;
					motor[backRight]  = gospeed*direction;
					motor[frontLeft]  = gospeed*direction;
					motor[backLeft]   = -gospeed*direction;
					wait1Msec(1);
				}
				//if moving right and back leads, slow down back motors
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[frontLeft])) && (direction==1))
				{
					motor[frontRight] = -gospeed;
					motor[backRight]  = (gospeed-delta);
					motor[frontLeft]  = gospeed;
					motor[backLeft]   = -(gospeed-delta);
					wait1Msec(1);
				}
				//if moving left and back leads, slow down back motors
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[frontLeft])) && (direction==-1))
				{
					motor[frontRight] = gospeed;
					motor[backRight]  = -(gospeed-delta);
					motor[frontLeft]  = -gospeed;
					motor[backLeft]   = (gospeed-delta);
					wait1Msec(1);
				}
				//if moving right and front leads, slow down front motors
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[frontLeft])) && (direction==1))
				{
					motor[frontRight] =  -(gospeed-delta);
					motor[backRight]  =  gospeed;
					motor[frontLeft]  =  (gospeed-delta);
					motor[backLeft]   =  -gospeed;
					wait1Msec(1);
				}
				//if moving left and front leads, slow down front motors
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[frontLeft])) && (direction==-1))
				{
					motor[frontRight] = (gospeed-delta);
					motor[backRight]  = -gospeed;
					motor[frontLeft]  = -(gospeed-delta);
					motor[backLeft]   = gospeed;
					wait1Msec(1);
				}
				else stopmotors();
			}
			stopmotors();
		}
	}
}
//88888888888888888888888888888    spin  8888888888888888888888888888888888
void spinbot(int xx2, int rotdir)
{
	//Determine direction of rotation 1 is Right 0 is Left
	if (rotdir == 1) xx2= -xx2;
	if (rotdir == 0) xx2=  xx2;

	motor[frontRight] =  xx2;
	motor[backRight]  =  xx2;
	motor[frontLeft]  = - xx2;
	motor[backLeft]   = - xx2;

	//stop the robot
	//stopmotors();
	wait1Msec (1);
}
//88888888888888888888888888888    ROBOT TURN MOVEMENT  8888888888888888888888888888888888
//calls the turn motor routine once the desired angle is determined
void turnrobot(int angle, int direction, int speed)
{
	int gyropos = 0, desiredangle = 0;
	//get current sensor position
	gyropos = SensorValue[gyro];

	//writeDebugStreamLine("gyropos is: %d", gyropos);  // writes the current value of int 'x' to the debug stream
	if (direction == 0)//this is a left turn
		desiredangle = gyropos + angle*10;
	else if (direction == 1)//this is a right turn
		desiredangle = gyropos - angle*10;
	//writeDebugStreamLine(", desiredangle is: %d", desiredangle);  // writes the current value of int 'x' to the debug stream

	while(abs(SensorValue[gyro] - desiredangle) > 10)
	{
		//writeDebugStreamLine("c angle: %d", abs(SensorValue[gyro] - desiredangle));  // writes the current value of int 'x' to the debug stream

		//call the spin right function; pass (x1, x2, y2, duration)
		spinbot(speed,direction);

		//writeDebugStream("gyro value: %d", SensorValue[gyro]);  // writes the current value of int 'x' to the debug stream
	}
	//Call stop motors function after turning
	stopmotors();
}
void smoverobot(int xx1, int xx2, int yy1, int duration, int automode)
{
	if (automode==0)
	{
		motor[frontRight] = yy1 - xx2 - xx1;
		motor[backRight]  =  yy1 - xx2 + xx1;
		motor[frontLeft]  = yy1 + xx2 + xx1;
		motor[backLeft]   =  yy1 + xx2 - xx1;

	}
	//This section is for automous mode movement of the base
	if (automode==1)
	{
		motor[frontRight] = (yy1 - xx2 - xx1);
		motor[backRight]  =  (yy1 - xx2 + xx1);
		motor[frontLeft]  = (yy1 + xx2 + xx1);
		motor[backLeft]   =  (yy1 + xx2 - xx1);

		wait1Msec(duration);

		//Stop the robot
		stopmotors();
	}
}

//88888888888888888888888888888  flywheels  8888888888888888888888888888888888
//88888888888888888888888888888  intake  8888888888888888888888888888888888
void intake(int speed, int dir, int on_off)
{
	//on
	if(on_off == 0)
	{
		//forword
		if(dir == 0)
		{
			motor[intakeMot] = speed;
		}
		//backwords
		if(dir == 1)
		{
			motor[intakeMot] = -speed;
		}
	}
	//off
	if(on_off == 1)
	{
		motor[intakeMot] = 0;
	}
}
//88888888888888888888888888888  shoot  8888888888888888888888888888888888
int speedL = 40;
int speedR = 40;
int minRPM;
void shoot(int on_off,int  minRpm)
{
	minRPM = minRpm;
	//on
	if(on_off == 0)
	{
		SetMotor(LeftShootT,speedL);
		SetMotor(LeftShootB,speedL);
		SetMotor(RightShootB,speedR);
		SetMotor(RightShootT,speedR);
	}
	//off
	if(on_off == 1)
	{
		SetMotor(LeftShootT,0);
		SetMotor(LeftShootB,0);
		SetMotor(RightShootB,0);
		SetMotor(RightShootT,0);
	}
}
//88888888888888888888888888888  smart intake  8888888888888888888888888888888888
void smartIntake(int iSpeed, int minRPM, int ShootOn_Off)
{
	shoot(ShootOn_Off, minRPM);

	if(SmartMotorGetSpeed(RightShootT) >= minRPM && SmartMotorGetSpeed(LeftShootT) >= minRPM)
	{
		intake(iSpeed, 0, 0);//both sides meet min RPM, then start intake
	}
	else
	{
		intake(iSpeed, 0, 1);//either side doens't min RPM
	}
}

//88888888888888888888888888888    LCD READOUT  8888888888888888888888888888888888
task lcd()
{
	int xbat;
	string num;
	string number;
	//bat num
	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery;
	string armbattery;
	string speedRight;
	string speedLeft;
	int mode = 1;
	int range = 3;
	int time = 1;
	int RMult = 3;
	int LMult = 3;

	while(1==1)
	{
		//right side
		if(SmartMotorGetSpeed(RightShootT) < minRPM - range)
		{
			if(minRPM != 0)
			{
				RMult = SmartMotorGetSpeed(RightShootT)/minRPM;
				LMult = SmartMotorGetSpeed(LeftShootT)/minRPM;
			}
			else if(minRPM == 0)
			{
				RMult = 0;
				LMult = 0;
			}
			speedR += RMult;// right side more than 20 below the min RPM, then increase by 1
		}
		else if(SmartMotorGetSpeed(RightShootT) > minRPM + range)
		{
			speedR -= RMult;// right side more than 20 above the max RPM, then decrease the right side by 1
		}
		//left side
		if(SmartMotorGetSpeed(LeftShootT) < minRPM - range)
		{
			if(minRPM != 0)
			{
				RMult = abs(SmartMotorGetSpeed(RightShootT)/minRPM);
				LMult = abs(SmartMotorGetSpeed(LeftShootT)/minRPM);
			}
			else if(minRPM == 0)
			{
				RMult = 0;
				LMult = 0;
			}

			speedL += LMult;// left side more than 20 above the min RPM, then increase the right side by 1
		}
		else if(SmartMotorGetSpeed(LeftShootT) > minRPM + range)
		{
			speedL -= LMult;// right side more than 20 above the max RPM, then decrease the right side by 1
		}
		if(speedL < 0)
		{
			speedL = 0;
		}
		else if(speedL > 127)
		{
			speedL = 127;
		}
		if(speedR < 0)
		{
			speedR = 0;
		}
		else if(speedR > 127)
		{
			speedR = 127;
		}
		//888888888888888888888888888 End of Speed Code, Start of LCD 888888888888888888888888888

		if(nLCDButtons != 0)
		{
			mode = nLCDButtons;
			clearLCDLine(0);// Clear line 1 (0) of the LCD
			clearLCDLine(1);// Clear line 2 (1) of the LCD
		}

		if(mode == 1)
		{
			//Display the Primary Robot battery voltage
			displayLCDString(0,0, "bat:");
			displayLCDString(1,0, "armbat:");
			sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
			sprintf(armbattery, "%1.2f%c", SensorValue[bat]/297.0,'V');
			displayLCDString(0,4, mainBattery);
			displayLCDString(1,7, armbattery);
		}
		else if(mode == 2)
		{
			sprintf(speedRight, "%4.2f%c", SmartMotorGetSpeed(RightShootT)*10,"RPM"); //Build the value to be displayed
			sprintf(speedLeft, "%4.2f%c", SmartMotorGetSpeed(LeftShootT)*10,"RPM"); //Build the value to be displayed
			displayLCDString(0,0, speedRight);
			displayLCDString(1,0, speedLeft);
		}
		else if(mode == 4)
		{
			displayLCDNumber(0,0, speedR);
			displayLCDNumber(1,0, speedL);
		}
		wait1Msec(time);
	}
}
//88888888888888888888888888888  arm  8888888888888888888888888888888888
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//88888888888888888888888888888    ARM MOVEMENT  8888888888888888888888888888888888
//void movearm(int arm, int duration, int holdarm, int holdarmpos)
//{
//	if (holdarm==0)
//	{
//		motor[topRight]     = arm;
//		motor[bottomRight]  = arm;
//		motor[topLeft]      = arm;
//		motor[bottomLeft]   = arm;
//		//writeDebugStream(" %d",SensorValue[Wrist], " %d");
//		//writeDebugStreamLine("holdarm is: %d",holdarm );  // writes the current value of int 'x' to the debug stream
//		wait1Msec(duration);
//	}

//	//the section below commands arm to selected positions.  There is no position hold feature
//	//there is no requirement for use of "abs" because count will always be positive if arm
//	//is set during initialization of robot (pre auton)
//	if (holdarm==1)
//	{
//		while ((nMotorEncoder[topRight] > (holdarmpos+40)) || (nMotorEncoder[topRight] < (holdarmpos-40)))
//		{
//			if (nMotorEncoder[topRight]<holdarmpos) //if below selected point, move up toward it at "arm" speed
//			{
//				motor[topRight]     = arm;
//				motor[bottomRight]  = arm;
//				motor[topLeft]      = arm;
//				motor[bottomLeft]   = arm;
//				wait1Msec(80); //select for arm motion smoothness - too big a number will cause arm
//				//to move too fast and shoot past mid point
//			}
//			else if (nMotorEncoder[topRight]>holdarmpos) //if above selected point, move down toward it at "arm" speed
//			{
//				motor[topRight]     = -arm*2/3; //motion slowed when moving down to prevent overshoot
//				motor[bottomRight]  = -arm*2/3;
//				motor[topLeft]      = -arm*2/3;
//				motor[bottomLeft]   = -arm*2/3;
//				wait1Msec(10);
//			}
//			else // otherwise stop all arm motors
//			{
//				stoparm();
//			}
//		}
//			stoparm();
//		wait1Msec(5);
//	}
//}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//88888888888888888888888888888    WRIST MOVEMENT  8888888888888888888888888888888888

//void  movewrist (int wristspd, int duration, int aton, int wristposit)
//{
//	//int checking=0;//variable to allow checking of delta count check
//	int wristspot = 450;
//	if (aton==0)
//	{
//		if (SensorValue[intmotencW] <= wristspot){
//			motor[RightWrist] = wristspd*0.6;
//			motor[LeftWrist] = wristspd*0.6;
//		}
//		else if (SensorValue[intmotencW] > wristspot){
//			motor[RightWrist] = wristspd;
//			motor[LeftWrist] = wristspd;
//		}
//		//writeDebugStreamLine("wristangle is: %d",SensorValue[wrist] );
//		wait1Msec(duration);
//	}
//	if (aton==1)
//	{
//		while ((abs(nMotorEncoder[RightWrist]) > (abs(wristposit)+200))||(abs(nMotorEncoder[RightWrist]) < (abs(wristposit)-200)))
//		{
//			if (nMotorEncoder[RightWrist] > wristposit)
//			{
//				motor[RightWrist] = wristspd;
//				motor[LeftWrist] = wristspd;
//				wait1Msec(10);
//			}
//			if (nMotorEncoder[RightWrist] < wristposit)
//			{
//				motor[RightWrist] = -wristspd;
//				motor[LeftWrist] = -wristspd;
//				wait1Msec(10);
//			}
//			else
//			{
//				motor[RightWrist] = 0;
//				motor[LeftWrist] = 0;
//			}
//		}
//		motor[RightWrist] = 0;
//		motor[LeftWrist] = 0;
//	}
//}

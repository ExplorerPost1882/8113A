#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "9-15-16 includes.c"				 //main user code has all the voids...no need to modify.

void pre_auton()
{
	bStopTasksBetweenModes = true;
	//reset incoders
	//nMotorEncoder[RightShootE]=0;
	//reset gyro
	SensorType[gyro] = 0;
	wait1Msec(50);
	SensorType[gyro] = sensorGyro;
	wait1Msec(1300);
	//angle is in degrees - multiplying by 10 done in the turn function
	//Adjust SensorFullCount to set the "rollover" point. A value of 3600 sets the rollover point to +/-3600
	SensorFullCount[gyro] = 7200;
}

task autonomous()
{
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)

	//if (SensorValue[RedOrBlue] == 0) //blue
	//{
	//	if (SensorValue[SkyOrNot] == 0)//not skyrise
	//	{
	//	}
	//	if (SensorValue[SkyOrNot] == 1)//blue skyrise auton
	//	{

	//	}
	//}
	//if (SensorValue[RedOrBlue] == 1)//red
	//{
	//	if (SensorValue[SkyOrNot] == 0) //not skyrise
	//	{

	//	}
	//	if (SensorValue[SkyOrNot] == 1)//red skyrise auton
	//	{
	//	}
	//}
}

task usercontrol()
{
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	startTask(lcd);
	int X1 = 0, Y1 = 0, X2 = 0,Y2 = 0;
	int threshold = 20;
	while (true)
	{
		//Create "deadzone" for Y1/Ch3 (FORWARD/BACK)
		Y1 = (abs(vexRT[Ch3]) > threshold) ? (vexRT[Ch3]) : (0);
		//Create "deadzone" for X1/Ch4 (RIGHT/LEFT)
		X1 = (abs(vexRT[Ch4]) > threshold) ? (vexRT[Ch4]) : (0);
		//Create "deadzone" for X2/Ch1(Rotation of robot about z axis)
		X2 = (abs(vexRT[Ch1]) > threshold+10) ? (vexRT[Ch1]*2/3) : (0);
		//Create "deadzone" for X2/Ch1(Rotation of robot about z axis)
		Y2 = (abs(vexRT[Ch3Xmtr2]) > threshold+10) ? (vexRT[Ch3Xmtr2]*2/3) : (0);
		//call robot movement function
		moverobot(-X1,X2,-Y1*0.8,0,0,0);
	}
}

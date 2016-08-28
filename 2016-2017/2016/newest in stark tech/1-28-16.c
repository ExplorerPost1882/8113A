#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    bat,            sensorAnalog)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  RedOrBlue,      sensorDigitalIn)
#pragma config(Sensor, dgtl2,  LeftOrNot,      sensorDigitalIn)
#pragma config(Sensor, dgtl3,  LeftSonar,      sensorSONAR_raw)
#pragma config(Sensor, dgtl5,  RightSonar,     sensorSONAR_raw)
#pragma config(Sensor, dgtl7,  FrontSonar,     sensorSONAR_raw)
#pragma config(Sensor, dgtl9,  BackSonar,      sensorSONAR_raw)
#pragma config(Sensor, I2C_5,  RightShootE,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_6,  LeftShootE,     sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intakeMot,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port4,           LeftShootB,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           LeftShootT,    tmotorVex393_MC29, openLoop, reversed, driveLeft, encoderPort, I2C_6)
#pragma config(Motor,  port6,           RightShootB,   tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           RightShootT,   tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_5)
#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          intakePull,    tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "1-28-16 includes.c"				 //main user code has all the voids...no need to modify.
//speed
const int highspd    = 127;
const int medspd    = 100;
const int lowspd     = 40;
//shoot
//min 65
int nexNet = 39;
int nexNetRPM = 32;
int conner = 70;
int connerRPM = 55;
int smOF = 1;
int sSpeed = nexNet;
int iSpeed = highspd;
int minRPM = nexNetRPM;

void pre_auton()
{
	bStopTasksBetweenModes = false;
	//reset incoders
	nMotorEncoder[RightShootE]=0;
	nMotorEncoder[LeftShootE]=0;
	//start smart motor stuff
	SmartMotorsInit();
	SmartMotorLinkMotors(RightShootT, RightShootB);
	SmartMotorLinkMotors(LeftShootT, LeftShootB);
	SmartMotorsSetEncoderGearing(RightShootT, 10.0);
	SmartMotorsSetEncoderGearing(LeftShootT, 10.0);
	SmartMotorsAddPowerExtender(LeftShootT, LeftShootB, RightShootB, RightShootT);
	SmartMotorSetPowerExpanderStatusPort(in1);
	SmartMotorSetFreeRpm(RightShootT, 90);
	SmartMotorSetFreeRpm(LeftShootT, 90);
	SmartMotorRun();
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
	startTask(lcd);
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	//intake(speed, der, on_off)
	//shoot(speed ,on_off, minRpm)
	while(1)
	{
		motor[intakePull] = highspd;
		smartIntake(iSpeed, sSpeed, minRPM, 0);
	}
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
	startTask(lcd);
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	//intake(speed, der, on_off)
	//shoot(speed ,on_off, minRpm)
	//smartIntake(int iSpeed,int sSpeed,int minRPM,int ShootOn_Off)
	int X1 = 0, Y1 = 0, X2 = 0,Y2 = 0;
	int threshold = 20;
	while (true)
	{
		motor[intakePull] = highspd;
		//Create "deadzone" for Y1/Ch3 (FORWARD/BACK)
	Y1 = (abs(vexRT[Ch3]) > threshold) ? (vexRT[Ch3]) : (0);

		//
		//Create "deadzone" for X1/Ch4 (RIGHT/LEFT)
	X1 = (abs(vexRT[Ch4]) > threshold) ? (vexRT[Ch4]) : (0);

		//
		//Create "deadzone" for X2/Ch1(Rotation of robot about z axis)
	X2 = (abs(vexRT[Ch1]) > threshold+10) ? (vexRT[Ch1]*2/3) : (0);

		//
		//Create "deadzone" for X2/Ch1(Rotation of robot about z axis)
	Y2 = (abs(vexRT[Ch3Xmtr2]) > threshold+10) ? (vexRT[Ch3Xmtr2]*2/3) : (0);
		//call robot movement function
		moverobot(-X1,X2,-Y1*0.8,0,0,0);
		smartIntake(iSpeed, sSpeed, minRPM, vexRT(Btn6U));
		//			irrelevant, 60, 		70,
		if(Btn8D = 1)
		{
			int sSpeed = nexNet;
			int minRPM = nexNetRPM;
		}
		else if(Btn8R = 1)
		{
			int sSpeed = nexNet;
			int minRPM = nexNetRPM;
		}

	}
}

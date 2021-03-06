#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    bat,            sensorNone)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  RedOrBlue,      sensorDigitalIn)
#pragma config(Sensor, dgtl2,  SkyOrNot,       sensorDigitalIn)
#pragma config(Sensor, dgtl3,  graypost,       sensorTouch)
#pragma config(Sensor, I2C_1,  LeftShootE,     sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  RightShootE,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           LeftShoot,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port6,           RightShoot,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port9,           backLeft,      tmotorVex393_MC29, openLoop, reversed, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"
#include "9-24-15 includes.c"
#include "SmartMotorLib.c"


const int highspd    = 127;
const int medspd    = 95;
const int lowspd     = 40;

/////////////////////////////////
void pre_auton()
{
	bStopTasksBetweenModes = false;
	nMotorEncoder[LeftShootE]=0;
	nMotorEncoder[RightShootE]=0;


	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[gyro] = 0;
	wait1Msec(50);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[gyro] = sensorGyro;
	wait1Msec(1300);
	clearDebugStream();
	//writeDebugStream("just finished gyro cal");  // writes the current value of int 'x' to the debug stream

	//********************************

	//angle is in degrees - multiplying by 10 done in the turn function
	//Adjust SensorScale to correct the scaling for your gyro
	//SensorScale[in8] = 260;
	//Adjust SensorFullCount to set the "rollover" point. A value of 3600 sets the rollover point to +/-3600
	SensorFullCount[gyro] = 7200;
	//all angles are a multiple of 10 (90 degrees is annotated at 900)
	//Error specifies the amount of acceptable error in the turn
	//*******************************
}

//********************************************************************************************************************************************************
task autonomous()
{
	startTask(lcd);
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	//movearm (speed,duration,holdarm,holdarmpos)
	//movewrist (wristspd,duration,holdwrist,holdwristangle)
	int X1 = 0, Y1 = 0, X2 = 0,  Wrist1=0, Arm1=0, wtime = 0, desiredangle = 0;
	int gyropos = 0, angle = 0, direction = 0, holdthearm = 0, holdthewrist = 0;
	int threshold = 20, JVI = 1, slowdown = 0, armholdpos = 0, wristholdangle = 0;
	int spinfast=50, spinslow=30;

	if (SensorValue[RedOrBlue] == 0) //blue
	{
		if (SensorValue[SkyOrNot] == 0)//not skyrise
		{
		}
		if (SensorValue[SkyOrNot] == 1)//blue skyrise auton
		{

		}
	}
	if (SensorValue[RedOrBlue] == 1)//red
	{
		if (SensorValue[SkyOrNot] == 0) //not skyrise
		{

		}
		if (SensorValue[SkyOrNot] == 1)//red skyrise auton
		{
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
task usercontrol()
{
	startTask(lcd);
	int X1 = 0, Y1 = 0, X2 = 0,Y2 = 0,  Wrist1=0, Arm1=0, wtime = 0, desiredangle = 0;
	int gyropos = 0, angle = 0, direction = 0, holdthearm = 0, holdthewrist = 0;
	int threshold = 20, JVI = 1, slowdown = 0, armholdpos = 0, wristholdangle = 0;
	int spinfast=50, spinslow=30;

	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	//enter user hcontrol segment
	//Loop Forever
	//clearDebugStream();
	SmartMotorsInit();
	SmartMotorRun();
	while(1)
	{
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//create deadzones ALSO SLOWS DOWN THE ROBOT BY "SLOWDOWN" IF SELECTED
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
		moverobot(-X1,X2,Y1*0.8,0,0,0);
		if (vexRT[Btn8D] == 1)
		{
			motor[intake] = 127;
		}
		else if (vexRT[Btn8D] != 1)
		{
			motor[intake] = 0;
		}
		//motor[RightShoot] = 127;
		motor[LeftShoot] = 127;
		SetMotor( RightShoot, 127);
		string speed;
		sprintf( speed, "%7.2f %7.2f", SmartMotorGetSpeed( LeftShoot ), SmartMotorGetSpeed( RightShoot ));
		displayLCDString(0,0, speed);
	}
}

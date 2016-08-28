#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    bat,            sensorNone)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  RedOrBlue,      sensorDigitalIn)
#pragma config(Sensor, dgtl2,  SkyOrNot,       sensorDigitalIn)
#pragma config(Sensor, I2C_1,  intmotencFL,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  intmotencBL,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  intmotencBR,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  intmotencARM,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_5,  intmotencW,     sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LeftWrist,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_3)
#pragma config(Motor,  port4,           topRight,      tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_4)
#pragma config(Motor,  port5,           bottomRight,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           topLeft,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port7,           bottomLeft,    tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, openLoop, reversed, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port9,           backLeft,      tmotorVex393_MC29, openLoop, reversed, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port10,          RightWrist,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_5)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"
#include "AATB 4-11-15.c"


const int highspd    = 127;
const int medspd    = 95;
const int lowspd     = 40;

const int stowarm    = 20;

//add 50 to all arm positions required and ensure you run arm at lowspd if lowering
//skyrise
const int armtwrsect1  = 475;
const int wristtwrsect1 = 1870;

const int armtwrsect2   = 555;
const int wristtwrsect2 = 270;

const int armtwrsect3   = 690;
const int wristtwrsect3 = 2200;

const int armtwrsect4   = 860;
const int wristtwrsect4 = 2360;

const int armtwrsect5   = 1010;
const int wristtwrsect5 = 2160;
//post
const int armhighpost   = 975;
const int wristhighpost = 2115;

const int armmiddlepost   = 885;
const int wristmiddlepost = 475;

const int armlowpost   = 570;
const int wristlowpost = 1725;

const int armcubeload   = 200;
const int wristcubeload = 525;

const int armtwrload = 96;
const int wristtwrload = 1497;

const int armtwrgrab = 400;
const int armtwrliftout = 580;


/////////////////////////////////
void pre_auton()
{
	lcd();
	nMotorEncoder[backLeft]=0;
	nMotorEncoder[backRight]=0;
	nMotorEncoder[frontLeft]=0;
	nMotorEncoder[topRight]=0;
	nMotorEncoder[RightWrist]=0;

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
	lcd();
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	//movearm (speed,duration,holdarm,holdarmpos)
	//movewrist (wristspd,duration,holdwrist,holdwristangle)
	int X1 = 0, Y1 = 0, X2 = 0,  Wrist1=0, Arm1=0, wtime = 0, desiredangle = 0;
	int gyropos = 0, angle = 0, direction = 0, holdthearm = 0, holdthewrist = 0;
	int threshold = 20, JVI = 1, slowdown = 0, armholdpos = 0, wristholdangle = 0;
	int spinfast=50, spinslow=30;
	if (SensorValue[RedOrBlue] == 1)//red
	{
		if (SensorValue[SkyOrNot] == 0) //not skyrise
		{
			//backup
			moverobot(0,0,2000,0,1,highspd);
			//smoverobot(0,0,-40,2500,1);
			wait1Msec (10);
			//armup
			movearm(lowspd+20,0,1,512);
			wait1Msec (10);
			//wristout & down
			movewrist (highspd,0,1,2500);
			wait1Msec (10);
			//backup
			moverobot(0,0,-1100,0,1,highspd);
			//rotate right
			turnrobot(530,1,medspd-10);
			//backup
			moverobot(0,0,-800,0,1,medspd);
			// go to qube load hight
			movewrist(highspd,0,1,1400);
			movearm(medspd-20,0,1,50);
			wait1Msec(10);
			//forward
			moverobot(0,0,600+25,0,1,highspd);
			wait1Msec(10);
			//go to middle post
			movearm(medspd-20,0,1,armmiddlepost+15);
			movewrist(highspd,0,1,wristmiddlepost);
			wait1Msec(20);
			//tun right
			turnrobot(190,1,medspd);
			wait1Msec(10);
			//forwodrd
			moverobot(0,0,450,0,1,highspd);
			wait1Msec(10);
			//arm down
			movearm(lowspd,0,1,770);
			wait1Msec(10);
			//wrist down
			movewrist(highspd,0,1,3500);
			wait1Msec(10);
		}
		if (SensorValue[SkyOrNot] == 1)//red skyrise auton
		{
			//out
			smoverobot(0,0,80,1600,1);
			wait1Msec (100);
			//right
			smoverobot(80,0,0,3200,1);
			wait1Msec (100);
			//rotate count-clock
			turnrobot(350,0,80);
			wait1Msec (100);
			//left
			smoverobot(-80,0,0,2500,1);
			wait1Msec (100);
			//roate clock
			turnrobot(360,1,80);
			wait1Msec (100);
			//forwords
			smoverobot(0,0,127,1600,1);
			wait1Msec (100);
			//left
			smoverobot(-100,0,0,3000,1);
			wait1Msec (100);
			//back
			smoverobot(0,0,-80,1000,1);
			wait1Msec (100);
			//right
			smoverobot(80,0,0,1400,1);
			wait1Msec (100);
			//left
			smoverobot(-80,0,0,500,1);
			wait1Msec (100);
		}
	}
	if (SensorValue[RedOrBlue] == 0) //blue
	{
		if (SensorValue[SkyOrNot] == 0)//not skyrise
		{
			//backup
			moverobot(0,0,-760,0,1,lowspd+35);
			wait1Msec (10);
			//armup
			movearm(lowspd+40,0,1,512);
			wait1Msec (10);
			//wrist down
			movewrist (highspd,0,1,1000);
			wait1Msec (10);
			//backup
			moverobot(0,0,-740,0,1,medspd);
			wait1Msec (10);
			//rotate right
			turnrobot(-510,1,medspd-10);
			wait1Msec (10);
			//backup
			moverobot(0,0,-550,0,1,medspd);
			wait1Msec (10);
			// go to qube load hight
			movewrist (highspd,0,1,wristcubeload);
			movearm(lowspd-15,0,1,armcubeload);
			wait1Msec (10);
			//forward
			moverobot(0,0,400,0,1,highspd);
			wait1Msec (10);
			//go to middle post
			movewrist (highspd,0,1,650);
			movearm(medspd-20,0,1,armlowpost);
			movewrist (highspd,0,1,400);
			movearm(medspd-20,0,1,armmiddlepost);
			movewrist (highspd,0,1,wristmiddlepost);
			wait1Msec (10);
			//turn right
			turnrobot(50,1,lowspd+20);
			wait1Msec (10);
			//forward
			moverobot(0,0,95,0,1,highspd);
			wait1Msec (10);
			//wrist down
			movewrist (highspd,0,1,1000);
			wait1Msec (10);
			//new*****************************************************************************************************
			//turn left
			turnrobot(70,0,lowspd+20);
			wait1Msec (10);
			//wrist load hight
			movewrist (highspd,0,1,wristcubeload);
			wait1Msec (10);
			//backup
			moverobot(0,0,-50,0,1,highspd);
			wait1Msec (10);
			//go right
			moverobot(2800,0,0,0,1,highspd);
			wait1Msec (10);
			//backup
			moverobot(0,0,-450,0,1,highspd);
			wait1Msec (10);
			//arm load hight
			movewrist (highspd,0,1,wristcubeload);
			movearm(lowspd,0,1,armcubeload+40);
			wait1Msec (10);
			//forword
			moverobot(0,0,375,0,1,highspd);
			wait1Msec (10);
			//arm then wrist at low post
			movearm(medspd-15,0,1,armlowpost);
			movewrist (highspd,0,1,wristlowpost);
			wait1Msec (10);
			//wrist down
			movewrist (highspd,0,1,1000);
			wait1Msec (10);
			//backup
			moverobot(0,0,-350,0,1,highspd);
			wait1Msec (10);
		}
		if (SensorValue[SkyOrNot] == 1)//blue skyrise auton
		{
			//froword
			moverobot(0,0,1100,0,1,highspd);
			wait1Msec (10);
			//rotte left
			turnrobot(430,0,highspd);
			wait1Msec (10);
			//right
			moverobot(3300,0,0,0,1,highspd);
			wait1Msec (10);
			//backup
			moverobot(0,0,-1600,0,1,highspd);
			wait1Msec (10);
			//forword
			moverobot(0,0,200,0,1,highspd);
			wait1Msec (10);
			//left
			moverobot(-3500,0,0,0,1,highspd);
			wait1Msec (10);
			//right
			moverobot(130,0,0,0,1,highspd);
			wait1Msec (10);
			//forword
			moverobot(0,0,1000,0,1,highspd);
			wait1Msec (10);
			//left
			moverobot(-300,0,0,0,1,highspd);
			wait1Msec (10);
			//forword
			moverobot(0,0,300,0,1,highspd);
			wait1Msec (10);
			//left
			moverobot(450,0,0,0,1,highspd);
			wait1Msec (10);
			//backup
			moverobot(0,0,-700,0,1,highspd);
			wait1Msec (10);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
task usercontrol()
{
	int X1 = 0, Y1 = 0, X2 = 0,  Wrist1=0, Arm1=0, wtime = 0, desiredangle = 0;
	int gyropos = 0, angle = 0, direction = 0, holdthearm = 0, holdthewrist = 0;
	int threshold = 20, JVI = 1, slowdown = 0, armholdpos = 0, wristholdangle = 0;
	int spinfast=50, spinslow=30;

	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	//enter user control segment
	//Loop Forever
	//clearDebugStream();

	while(1)
	{
		lcd();
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//this next section sets the user controls to joystick control
		//test for slow motion or full motion used for fine control around the towers
		if (vexRT[Btn6U]==0)
		{
			slowdown = 1;
			wait1Msec(15);
		}//will be used to divide commanded speeds by the selected value
		else if (vexRT[Btn6U]==1)
		{
			slowdown=3; //will be used to divide the commanded speeds by unity
			wait1Msec(15);
		}
		//*********

		//*********This test sets the arm to hold height selected on 2nd transmitter buttion 7U
		if (vexRT[Btn7UXmtr2]==1)
		{
			if (holdthearm == 1)
				holdthearm = 0;
			else if (holdthearm == 0)
			{
				holdthearm = 1;
				armholdpos = SensorValue[topRight];
			}
			wait1Msec(15);
		}
		//*********
		//*********This test sets the arm to hold height selected on 2nd transmitter buttion 8U
		if (vexRT[Btn8UXmtr2]==1)
		{
			if (holdthewrist == 1)
				holdthewrist = 0;
			else if (holdthewrist == 0)
			{
				holdthewrist = 1;
				wristholdangle = abs(SensorValue[RightWrist]-SensorValue[topRight]/.33);
				//writeDebugStreamLine("WRISTHOLDANGLE = %d", wristholdangle);  // writes the current value of int 'wristholdangle' to the debug stream
			}
			wait1Msec(40); //pause for button push
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//create deadzones ALSO SLOWS DOWN THE ROBOT BY "SLOWDOWN" IF SELECTED
		//Create "deadzone" for Y1/Ch3 (FORWARD/BACK)
	Y1 = (abs(vexRT[Ch3]) > threshold) ? (vexRT[Ch3]/slowdown) : (0);

		//
		//Create "deadzone" for X1/Ch4 (RIGHT/LEFT)
	X1 = (abs(vexRT[Ch4]) > threshold) ? (vexRT[Ch4]/slowdown) : (0);

		//
		//Create "deadzone" for X2/Ch1(Rotation of robot about z axis)
	X2 = (abs(vexRT[Ch1]) > threshold+10) ? (vexRT[Ch1]*2/3) : (0);

		//
		//Create "deadzone" for wristmove/Ch3 Wrist1
	Wrist1 = (abs(vexRT[Ch2Xmtr2]) > threshold) ? (vexRT[Ch2Xmtr2]*2/3) : (0);

		//
		//Create "deadzone" for Arm Movement (Arm1)
		//
	Arm1 = (abs(vexRT[Ch3Xmtr2]) > threshold) ? (vexRT[Ch3Xmtr2]/2) : (0);

		//call robot movement function
		moverobot(X1,X2,Y1*0.8,0,0,0);
		//int speedtemp = 30;
		//motor[backLeft] = speedtemp + 0;
		//motor[backRight] = speedtemp + 0;
		//motor[frontLeft] = speedtemp + 0;
		//motor[frontRight] = speedtemp + 0;
		//call robot arm movement function
		movearm(Arm1,0,0,0);

		//wrist movement
		movewrist(Wrist1*0.66,0,0,0);

		//tower hight
		//high
		if (vexRT(Btn8UXmtr2) == 1)
		{
			movearm(lowspd,0,1,armhighpost);
			movewrist(highspd,0,1,wristhighpost);
			wait1Msec(2000);
		}
		//middle
		if (vexRT(Btn8RXmtr2) == 1)
		{
			movearm(lowspd,0,1,armmiddlepost);
			movewrist(highspd,0,1,wristmiddlepost);
			wait1Msec(2000);
		}
		//low
		if (vexRT(Btn8LXmtr2) == 1)
		{
			movearm(lowspd,0,1,armlowpost);
			movewrist(highspd,0,1,wristlowpost);
			wait1Msec(2000);
		}
		//load
		if (vexRT(Btn8DXmtr2) == 1)
		{
			movearm(lowspd,0,1,armcubeload);
			movewrist(highspd,0,1,wristcubeload);
			wait1Msec(2000);
		}
		//skyrise hight
		//5
		if (vexRT(Btn5UXmtr2) == 1)
		{
			movearm(lowspd,0,1,armtwrsect5);
			movewrist(highspd,0,1,wristtwrsect5);
			wait1Msec(20);
		}
		//4
		if (vexRT(Btn5DXmtr2) == 1)
		{
			movearm(lowspd,0,1,armtwrsect4);
			movewrist(highspd,0,1,wristtwrsect4);
			wait1Msec(20);
		}
		//3
		if (vexRT(Btn7UXmtr2) == 1)
		{
			movearm(lowspd,0,1,armtwrsect3);
			movewrist(highspd,0,1,wristtwrsect3);
			wait1Msec(20);
		}
		//2
		if (vexRT(Btn7RXmtr2) == 1)
		{
			movearm(lowspd,0,1,armtwrsect2);
			movewrist(highspd,0,1,wristtwrsect2);
			wait1Msec(20);
		}
		//1
		if (vexRT(Btn7LXmtr2) == 1)
		{
			movearm(lowspd,0,1,armtwrsect1);
			movewrist(highspd,0,1,wristtwrsect1);
			wait1Msec(20);
		}
		//load
		if (vexRT(Btn7DXmtr2) == 1)
		{
			movearm(lowspd,0,1,15);
			movewrist(highspd,0,1,15);
			wait1Msec(20);
		}
	}
}

#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    bat,            sensorAnalog)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  RedOrBlue,      sensorDigitalIn)
#pragma config(Sensor, dgtl2,  LeftOrNot,      sensorDigitalIn)
#pragma config(Sensor, dgtl3,  Skils,          sensorDigitalIn)
#pragma config(Sensor, I2C_1,  intmotencFL,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  intmotencBL,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  intmotencBR,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  intmotencARM,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  intmotencW,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           frontRight,    tmotorVex393_HBridge, openLoop, reversed, driveLeft)
#pragma config(Motor,  port2,           vClaw,         tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, reversed, driveRight, encoderPort, I2C_1)
#pragma config(Motor,  port4,           topRight,      tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_5)
#pragma config(Motor,  port5,           bottomRight,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           topLeft,       tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port7,           bottomLeft,    tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_3)
#pragma config(Motor,  port9,           bottomArm,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_4)
#pragma config(Motor,  port10,          backLeft,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

//varables
int up = 900;
int throw = 1100;
int Pickup = 125;
int down = 0;
int drive = 500;
int armHol = 0;
int nockStar = 900;
int pos = 125;
//speeds
const int highspd = 127;
const int medspd = 95;
const int lowspd = 40;

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "10-22-16 includes.c"				 //main user code has all the voids...no need to modify.

void pre_auton()
{
	bStopTasksBetweenModes = true;
	//reset incoders
	nMotorEncoder[frontLeft]=0;
	nMotorEncoder[frontRight]=0;
	nMotorEncoder[backLeft]=0;
	nMotorEncoder[backRight]=0;
	nMotorEncoder[topRight]=0;
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
	//startTask(lcdAndArm);
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	//movearm (speed,duration,holdarm,holdarmpos)                                                    mmmmm;
	/*
	if (SensorValue[RedOrBlue] == 0) //blue
	{
	if (SensorValue[SkyOrNot] == 0)//blue left
	{

	}
	if (SensorValue[SkyOrNot] == 1)//blue Right
	{

	}
	}
	if (SensorValue[RedOrBlue] == 1)//red
	{
	if (SensorValue[SkyOrNot] == 0) //red right
	{

	}
	if (SensorValue[SkyOrNot] == 1)//red left
	{
	}
	}

	if(SensorValue[Skils] == 1)//skills feald
	{
		win();*/

		//SKILS Autonomous
		motor[topLeft]=70;
		motor[topRight]=70;
		motor[bottomLeft]=70;
		motor[bottomRight]=70;
		motor[bottomArm]=70;
		wait1Msec(950);

		motor[topLeft]=0;
		motor[topRight]=0;
		motor[bottomLeft]=0;
		motor[bottomRight]=0;
		motor[bottomArm]=0;
		wait1Msec(200);

		motor[vClaw]=100;
		//motor[vClawR]=100;
		wait1Msec(495);

		motor[vClaw]=0;
		//motor[vClawR]=0;
		wait1Msec(150);

		motor[frontLeft]=80;
		motor[frontRight]=80;
		motor[backLeft]=80;
		motor[backRight]=80;
		wait1Msec(2500);

		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(100);

		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(1050);

		/*motor[vClaw]=100;
		wait1Msec(100);

		motor[vClaw]=-100;
		wait1Msec(100);

		motor[vClaw]=0;
		wait1Msec(100);

		motor[frontLeft]=-70;
		motor[frontRight]=-70;
		motor[backLeft]=-70;
		motor[backRight]=-70;
		wait1Msec(500);

		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(100);

		motor[frontLeft]=-70;
		motor[frontRight]=70;
		motor[backLeft]=-70;
		motor[backRight]=70;
		wait1Msec(100);

		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(100);

		/*motor[frontLeft]=-80;
		motor[frontRight]=-80;
		motor[backLeft]=-80;
		motor[backRight]=-80;
		wait1Msec(650);

		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(1000);

		motor[vClaw]=270;
		wait1Msec(1000);

		motor[topLeft]=70;
		motor[topRight]=70;
		motor[bottomLeft]=70;
		motor[bottomRight]=70;
		wait1Msec(550);

		motor[vClaw]=120;
		wait1Msec(650);

		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(700);

		motor[vClaw]=-120;
		wait1Msec(280);

		motor[vClaw]=0;
		wait1Msec(14000);


		motor[topLeft]=20;
		motor[topRight]=20;
		motor[bottomLeft]=20;
		motor[bottomRight]=20;
		wait1Msec(53);
		//brings arm up a bit so that the claw can come out
		motor[topLeft]=0;
		motor[topRight]=0;
		motor[bottomLeft]=0;
		motor[bottomRight]=0;
		wait1Msec(1);
		//stop the arm
		motor[frontLeft]=80;
		motor[frontRight]=80;
		motor[backLeft]=80;
		motor[backRight]=80;
		wait1Msec(1300);
		//go forward to cube
		motor[frontLeft]=0;
		motor[frontRight]=0;
		motor[backLeft]=0;
		motor[backRight]=0;
		wait1Msec(1);


		motor[vClaw]=97;
		wait1Msec(20);
		//slightly closes claw
		motor[frontLeft]=80;
		motor[frontRight]=80;
		motor[backLeft]=80;
		motor[backRight]=80;
		wait1Msec(1250);
		//go forward to wall
		motor[frontLeft]=-70;
		motor[frontRight]=70;
		motor[backLeft]=-70;
		motor[backRight]=70;
		wait1Msec(650);
		//turn 45 angle left
		motor[frontLeft]=-70;
		motor[frontRight]=70;
		motor[backLeft]=-70;
		motor[backRight]=70;
		wait1Msec(450);
		//goes to middle of field
		motor[topLeft]=90;
		motor[topRight]=90;
		motor[bottomLeft]=90;
		motor[bottomRight]=90;
		wait1Msec(750);
		//bring arm up to knock stars off of middle wall
		motor[topLeft]=-90;
		motor[topRight]=-90;
		motor[bottomLeft]=-90;
		motor[bottomRight]=-90;
		wait1Msec(650);
		//bring arm down slightly
		motor[frontLeft]=-80;
		motor[frontRight]=80;
		motor[backLeft]=-80;
		motor[backRight]=80;
		wait1Msec(500);
		//turn 90 angle (left) towards cube
		motor[vClaw]=-97;
		wait1Msec(350);
		//slightly opens claw
		motor[frontLeft]=90;
		motor[frontRight]=90;
		motor[backLeft]=90;
		motor[backRight]=90;
		wait1Msec(600);
		//goes straight to cube
		motor[vClaw]=110;
		wait1Msec(500);
		//closes claw onto cube
		motor[frontLeft]=-100;
		motor[frontRight]=-100;
		motor[backLeft]=-100;
		motor[backRight]=-100;
		wait1Msec(800);
		//backs up into wall
		motor[topLeft]=90;
		motor[topRight]=90;
		motor[bottomLeft]=90;
		motor[bottomRight]=90;
		wait1Msec(500);
		//raises arm over wall
		motor[vClaw]=-97;
		wait1Msec(500);
		//opens claw to release cube
		motor[topLeft]=-90;
		motor[topRight]=-90;
		motor[bottomLeft]=-90;
		motor[bottomRight]=-90;
		wait1Msec(500);
		//lowers arm*/



	}


task usercontrol()
{
	//turnrobot(angle,direction,speed);
	//moverobot(xx1,xx2,yy1,duration,automode,speed)
	//void movearm(speed,duration,holdarm,holdarmpos)
	startTask(lcdAndArm);
	int X1 = 0, Y1 = 0, X2 = 0;//,Y2 = 0;
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
		//Y2 = (abs(vexRT[Ch3Xmtr2]) > threshold+10) ? (vexRT[Ch3Xmtr2]*2/3) : (0);
		//call robot movement function
		moverobot(X1,X2,Y1*0.8,0,0,0);
		//put arm in throw position
		/*if(vexRT[Btn8UXmtr2] == 1)
		{
			armHol = 1;
			movearm(highspd,0,1,throw);
		}
		//put arm in picup position
		if(vexRT[Btn8DXmtr2] == 1)
		{
			armHol = 1;
			movearm(lowspd+10,0,1,Pickup);
		}
		//put arm in drive
		if(vexRT[Btn8RXmtr2] == 1)
		{
			armHol = 1;
			movearm(lowspd+15,0,1,drive);
		}
		//put arm in knock off
		if(vexRT[Btn8LXmtr2] == 1)
		{
			armHol = 1;
			movearm(lowspd+15,0,1,nockStar);
		}

		if(vexRT[Btn7UXmtr2] == 1)
		{
			motor[liftLeft] = 127;
			motor[liftRight] = 127;
		}
		if(vexRT[Btn7DXmtr2] == 1)
		{
			motor[liftLeft] = -127;
			motor[liftRight] = -127;
		}
		else if(vexRT[Btn7DXmtr2] == 0 &&  vexRT[Btn7UXmtr2] == 0)
		{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}

		//set pos
		if(vexRT[Btn6UXmtr2] == 1)
		{
			pos = nMotorEncoder[topRight];
		}
		//hold pos
		if(vexRT[Btn6DXmtr2] == 1)
		{
			armHol = 1;
			movearm(lowspd+15,0,1,pos);
		}

		//joy controel
		if(armHol == 0)
		{
			movearm(Y2,0,0,0);
		}
		////pur arm in mantanice
		//if(vexRT[Btn7UXmtr2] == 1)
		//{
		//	armHol = 1;
		//	movearm(lowspd,0,1,up);
		//}
		//lock and unlock arm controel
		if(vexRT[Btn5UXmtr2] == 1)
		{
			armHol = 1;
		}
		if(vexRT[Btn5DXmtr2] == 1)
		{
			armHol = 0;
		}*/
		motor[topLeft] = vexRT[Ch3Xmtr2];
		motor[topRight] = vexRT[Ch3Xmtr2];
		motor[bottomLeft] = vexRT[Ch3Xmtr2];
		motor[bottomRight] = vexRT[Ch3Xmtr2];
		motor[bottomArm] = vexRT[Ch3Xmtr2];
		motor[vClaw] = vexRT[Ch2Xmtr2];
		//motor[vClawR] = vexRT[Ch2Xmtr2];

		/*if(vexRT[Btn8LXmtr2] == 1)
		{
		motor[vClaw] = 90;
		}
		if(vexRT[Btn8RXmtr2] == 1)
		{
		motor[vClaw] = -90;
		}*/

	}
}

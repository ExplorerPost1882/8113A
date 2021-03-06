#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    bat,            sensorAnalog)
#pragma config(Sensor, I2C_5,  RightShootE,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_6,  LeftShootE,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           intakeMot,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port4,           LeftShootB,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           LeftShootT,    tmotorVex393_MC29, openLoop, reversed, driveLeft, encoderPort, I2C_6)
#pragma config(Motor,  port6,           RightShootB,   tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           RightShootT,   tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_5)
#pragma config(Motor,  port10,          intakePull,    tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "SmartMotorLib.c"				 //main code has all the voids...no need to modify.

//88888888888888888888888888888  flywheels  8888888888888888888888888888888888
//varavles
int stateI
//next to net
int nexNetRPM = 30;
//coner
int connerRPM = 55;
//shuuter speeds
int RPM = nexNetRPM;
//intake speed
int iSpeed = highspd;
//end varavles   8888888888888888888888888888888888
//add to main pre aton  8888888888888888888888888888888888
//start smart motor stuff
nMotorEncoder[LeftShootE]=0;
SmartMotorsInit();
SmartMotorLinkMotors(RightShootT, RightShootB);
SmartMotorLinkMotors(LeftShootT, LeftShootB);
SmartMotorsAddPowerExtender(LeftShootT, LeftShootB, RightShootB, RightShootT);
SmartMotorSetPowerExpanderStatusPort(in1);
SmartMotorSetFreeRpm(RightShootT, 90);
SmartMotorSetFreeRpm(LeftShootT, 90);
SmartMotorRun();
//end pre aton  8888888888888888888888888888888888
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
int speedL = 20;
int speedR = 20;
int minRPM;
void shoot(int on_off,int minRpm)
{
	minRPM = minRpm+10;
	//on
	if(on_off == 0)
	{
		writeDebugStreamLine("speedL:%d", speedL);
		writeDebugStreamLine("speedR:%d", speedR);

		SetMotor(LeftShootT,speedL);
		SetMotor(LeftShootB,speedL);
		SetMotor(RightShootB,speedR);
		SetMotor(RightShootT,speedR);
	}
	//off
	if(on_off == 1)
	{
		writeDebugStream("All motors -> 0")
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

	if(SmartMotorGetSpeed(RightShootT) >= minRPM-4 && SmartMotorGetSpeed(LeftShootT) >= minRPM-4)
	{
		if(minRPM != 0)
		{
			intake(iSpeed, 0, 0);//both sides meet min RPM, then start intake
		}
		if(minRPM == 0)
		{
			intake(0, 0, 1;//both sides meet min RPM but its zero the stop intake
		}
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
	string pen1L;
	string pen2L;
	int mode = 1;
	int time = 500;
	string speedRight;
	string speedLeft;
	double range = 2.5;
	int RMult = 3;
	int LMult = 3;

	while(1==1)
	{
		writeDebugStreamLine("difR:%d",abs(SmartMotorGetSpeed(RightShootT)-minRPM)/2);
		writeDebugStreamLine("difL:%d",abs(SmartMotorGetSpeed(LeftShootT)-minRPM)/2);

		//right side

		RMult = abs(SmartMotorGetSpeed(RightShootT)-minRPM)/2;

		if(SmartMotorGetSpeed(RightShootT) < minRPM - range)
		{
			speedR += RMult;
		}
		else if(SmartMotorGetSpeed(RightShootT) > minRPM + range)
		{
			speedR -= RMult;
		}

		//left side
		LMult = abs(SmartMotorGetSpeed(LeftShootT)-minRPM)/2;

		if(SmartMotorGetSpeed(LeftShootT) < minRPM - range)
		{
			speedL += LMult;
		}
		else if(SmartMotorGetSpeed(LeftShootT) > minRPM + range)
		{
			speedL -= LMult;
		}

		if(speedL < 0)//boundaries check
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
		//888888888888888888888888888 START OF LCD CODE 888888888888888888888888888
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
			displayLCDNumber(0,4, RMult);
			displayLCDNumber(1,4, LMult);
		}
		wait1Msec(time);
	}
}

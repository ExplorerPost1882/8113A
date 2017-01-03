//add to main
//#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
//#pragma config(I2C_Usage, I2C1, i2cSensors)
//#pragma config(Sensor, in1,    bat,            sensorNone)
//#pragma config(Sensor, I2C_1,  intmotencFL,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
//#pragma config(Sensor, I2C_2,  intmotencBL,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
//#pragma config(Sensor, I2C_3,  intmotencBR,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
//#pragma config(Sensor, I2C_4,  intmotencARM,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
//#pragma config(Sensor, I2C_5,  intmotencW,     sensorQuadEncoderOnI2CPort,    , AutoAssign)
//#pragma config(Motor,  port4,           topRight,      tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_4)
//#pragma config(Motor,  port5,           bottomRight,   tmotorVex393_MC29, openLoop, driveRight)
//#pragma config(Motor,  port6,           topLeft,       tmotorVex393_MC29, openLoop, driveLeft)
//#pragma config(Motor,  port7,           bottomLeft,    tmotorVex393_MC29, openLoop, reversed, driveLeft)
//#pragma config(Motor,  port10,          RightWrist,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_5)
////*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//add to main

//88888888888888888888888888888  arm  8888888888888888888888888888888888
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//88888888888888888888888888888    ARM MOVEMENT  8888888888888888888888888888888888
//ints for arm drive and arm lcd out
int armS;
int dur;
int armTP;

//drive the motors as commanded
void stoparm()
{
		motor[topRight]     = 0;
		motor[bottomRight]  = 0;
		motor[topLeft]      = 0;
		motor[bottomLeft]   = 0;
}

void movearm(int arm, int duration, int holdarm, int holdarmpos)
{
	armHol = holdarm;
	if (holdarm==0)
	{
		motor[topRight]     = arm;
		motor[bottomRight]  = arm;
		motor[topLeft]      = arm;
		motor[bottomLeft]   = arm;
		//writeDebugStream(" %d",SensorValue[Wrist], " %d");
		//writeDebugStreamLine("holdarm is: %d",holdarm );  // writes the current value of int 'x' to the debug stream
		wait1Msec(duration);
	}

	//the section below commands arm to selected positions.  There is no position hold feature
	//there is no requirement for use of "abs" because count will always be positive if arm
	//is set during initialization of robot (pre auton)
	if (holdarm==1)
	{
		armS = arm;
		dur = duration;
		armTP = holdarmpos;
	}
}

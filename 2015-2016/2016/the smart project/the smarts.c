#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    bat,            sensorAnalog)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  RedOrBlue,      sensorDigitalIn)
#pragma config(Sensor, dgtl2,  LeftOrNot,      sensorDigitalIn)
#pragma config(Sensor, dgtl3,  LeftSonar,      sensorSONAR_inch)
#pragma config(Sensor, dgtl5,  RightSonar,     sensorSONAR_inch)
#pragma config(Sensor, dgtl7,  FrontSonar,     sensorSONAR_inch)
#pragma config(Sensor, dgtl9,  BackSonar,      sensorSONAR_inch)
#pragma config(Sensor, I2C_5,  LeftShootE,     sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intakeMot,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port4,           LeftShootB,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           LeftShootT,    tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port6,           RightShootB,   tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           RightShootT,   tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_5)
#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

#include "11-21-15 includes.c"
#include "smarts.c"
#include "location.c"
//speed
const int highspd    = 127;
const int medspd    = 100;
const int lowspd     = 40;

task main()
{



}

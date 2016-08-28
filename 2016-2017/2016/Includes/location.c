void Boot()
{
	//reset incoders
	nMotorEncoder[LeftShootE]=0;
	//reset gyro
	SensorType[gyro] = 0;
	wait1Msec(50);
	SensorType[gyro] = sensorGyro;
	wait1Msec(1300);
	//find team color
	if(SensorValue(LeftSonar) == 1)
	{
		int side = 1;
	}
	if(SensorValue(RightSonar) == 1)
	{
		int side = 2;
	}
	//find tile
	if(SensorValue(BackSonar) > 1)
	{
		int tile = 1;
	}
	else
	{
		int tile = 2;
	}
	//find Location and save
	FindLocation();
}
void FindLocation()
{

}
void MoveToPosition(X , Y)
{

}
void locateballs()
{

}
void MoveToBalls()
{

}
void ShootBalls()
{

}
void CountBallls()
{

}
void movetoshoot()
{

}

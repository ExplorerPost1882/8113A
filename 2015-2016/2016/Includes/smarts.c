void findLocation()
{
	int X;
	int Y;
	if(SensorValue(FrontSonar)<72)
	{
		if(SensorValue(RightSonar)<72)
		{
			X=abs(SensorValue(RightSonar)-12);
			Y=abs(SensorValue(FrontSonar)-12);
		}
		else if(SensorValue(LeftSonar)<72)
		{
			X=abs(SensorValue(LeftSonar)-12);
			Y=abs(SensorValue(FrontSonar)-12);
		}
	}
	else if(SensorValue(BackSonar)<72)
	{
		if(SensorValue(RightSonar)<72)
		{
			X=SensorValue(RightSonar)-12;
			Y=SensorValue(BackSonar)-12;
		}
		else if(SensorValue(LeftSonar)<72)
		{
			X=SensorValue(LeftSonar)-12;
			Y=SensorValue(BackSonar)-12;
		}
	}
}
void MoveToPosition(int X2, int Y2)
{
	findLocation();
	int gyropost = SensorValue(gyro);
	turnrobot( , , highspd)
}

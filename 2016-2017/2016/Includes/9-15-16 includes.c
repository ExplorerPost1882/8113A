//88888888888888888888888888888 stop motors 8888888888888888888888888888888888
void stopmotors()
{
	motor[frontRight] = 0;
	motor[backRight]  = 0;
	motor[frontLeft]  = 0;
	motor[backLeft]   = 0;
	wait1Msec(10);
}
void moverobot(int xx1, int xx2, int yy1, int duration, int automode, int gospeed)
{
	int direction;
	int delta = 35;
	if (automode==0)
	{
		motor[frontRight] = yy1 - xx2 - xx1;
		motor[backRight]  =  yy1 - xx2 + xx1;
		motor[frontLeft]  = yy1 + xx2 + xx1;
		motor[backLeft]   =  yy1 + xx2 - xx1;
		wait1Msec(duration);

	}
	//This section is for automous mode movement of the base
	if (automode==1)
	{
		if(yy1!=0)//code for movement forward or reverse.  +yy1=forward, -yy1=reverse
		{
			if (yy1>0) direction=1;
			else if (yy1<0) direction=-1;
			//writeDebugStream("yy1= %d", yy1);  // writes the current value of int 'yy1' to the debug stream
			nMotorEncoder[backLeft]  = 0;
			nMotorEncoder[backRight] = 0;
			// this while loop moves the base until the desired distance - yy1 - is achieved
			while ((abs(nMotorEncoder[backLeft]) < (abs(yy1)-30)) || (abs(nMotorEncoder[backRight])<(abs(yy1)-30)))
				//  || ((nMotorEncoder[backLeft]>yy1+200)&&(-nMotorEncoder[backRight]>yy1+200)))
			{
				if (abs(nMotorEncoder[backLeft]) == abs(nMotorEncoder[backRight]))
				{
					motor[frontRight] = gospeed*direction;
					motor[backRight]  = gospeed*direction;
					motor[frontLeft]  = gospeed*direction;
					motor[backLeft]   = gospeed*direction;
					wait1Msec(1);
				}
				//if moving forward and left leads, slow down left side
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[backRight])) && (direction==1))
				{
					motor[frontRight] = gospeed;
					motor[backRight]  = gospeed;
					motor[frontLeft]  = (gospeed-delta);
					motor[backLeft]   = (gospeed-delta);
					wait1Msec(1);
				}
				//if moving backward and left leads, slow down left side
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[backRight])) && (direction==-1))
				{
					motor[frontRight] = -gospeed;
					motor[backRight]  = -gospeed;
					motor[frontLeft]  = -(gospeed-delta);
					motor[backLeft]   = -(gospeed-delta);
					wait1Msec(1);
				}
				//if moving forward and left lags, slow down right side
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[backRight])) && (direction==1))
				{
					motor[frontRight] =  (gospeed-delta);
					motor[backRight]  =  (gospeed-delta);
					motor[frontLeft]  =  gospeed;
					motor[backLeft]   =  gospeed;
					wait1Msec(1);
				}
				//if moving backward and left lags, slow down right side
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[backRight])) && (direction==-1))
				{
					motor[frontRight] = -(gospeed-delta);
					motor[backRight]  = -(gospeed-delta);
					motor[frontLeft]  = -gospeed;
					motor[backLeft]   = -gospeed;
					wait1Msec(1);
				}
				else stopmotors();
			}
			stopmotors();
		}
		if(xx1!=0)//code for movement left or right.  +xx1=right, -xx1=left
		{
			if (xx1>0) direction=1;
			if (xx1<0) direction=-1;

			nMotorEncoder[backLeft]  = 0;
			nMotorEncoder[frontLeft] = 0;

			while (( abs(nMotorEncoder[backLeft]) < (abs(xx1)-30))&&(abs(nMotorEncoder[frontLeft]) < (abs(xx1)-30)))
				//||((abs(nMotorEncoder[backLeft]) > abs(xx1+200)) && abs(nMotorEncoder[frontLeft]) > abs(xx1+200)))
			{
				//move right equally
				if (abs(nMotorEncoder[backLeft]) == abs(nMotorEncoder[frontLeft]))
				{
					motor[frontRight] = -gospeed*direction;
					motor[backRight]  = gospeed*direction;
					motor[frontLeft]  = gospeed*direction;
					motor[backLeft]   = -gospeed*direction;
					wait1Msec(1);
				}
				//if moving right and back leads, slow down back motors
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[frontLeft])) && (direction==1))
				{
					motor[frontRight] = -gospeed;
					motor[backRight]  = (gospeed-delta);
					motor[frontLeft]  = gospeed;
					motor[backLeft]   = -(gospeed-delta);
					wait1Msec(1);
				}
				//if moving left and back leads, slow down back motors
				else if ((abs(nMotorEncoder[backLeft]) > abs(nMotorEncoder[frontLeft])) && (direction==-1))
				{
					motor[frontRight] = gospeed;
					motor[backRight]  = -(gospeed-delta);
					motor[frontLeft]  = -gospeed;
					motor[backLeft]   = (gospeed-delta);
					wait1Msec(1);
				}
				//if moving right and front leads, slow down front motors
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[frontLeft])) && (direction==1))
				{
					motor[frontRight] =  -(gospeed-delta);
					motor[backRight]  =  gospeed;
					motor[frontLeft]  =  (gospeed-delta);
					motor[backLeft]   =  -gospeed;
					wait1Msec(1);
				}
				//if moving left and front leads, slow down front motors
				else if ((abs(nMotorEncoder[backLeft]) < abs(nMotorEncoder[frontLeft])) && (direction==-1))
				{
					motor[frontRight] = (gospeed-delta);
					motor[backRight]  = -gospeed;
					motor[frontLeft]  = -(gospeed-delta);
					motor[backLeft]   = gospeed;
					wait1Msec(1);
				}
				else stopmotors();
			}
			stopmotors();
		}
	}
}
//88888888888888888888888888888    spin  8888888888888888888888888888888888
void spinbot(int xx2, int rotdir)
{
	//Determine direction of rotation 1 is Right 0 is Left
	if (rotdir == 1) xx2= -xx2;
	if (rotdir == 0) xx2=  xx2;

	motor[frontRight] =  xx2;
	motor[backRight]  =  xx2;
	motor[frontLeft]  = - xx2;
	motor[backLeft]   = - xx2;

	//stop the robot
	//stopmotors();
	wait1Msec (1);
}
//88888888888888888888888888888    ROBOT TURN MOVEMENT  8888888888888888888888888888888888
//calls the turn motor routine once the desired angle is determined
void turnrobot(int angle, int direction, int speed)
{
	int gyropos = 0, desiredangle = 0;
	//get current sensor position
	gyropos = SensorValue[gyro];

	//writeDebugStreamLine("gyropos is: %d", gyropos);  // writes the current value of int 'x' to the debug stream
	if (direction == 0)//this is a left turn
		desiredangle = gyropos + angle*10;
	else if (direction == 1)//this is a right turn
		desiredangle = gyropos - angle*10;
	//writeDebugStreamLine(", desiredangle is: %d", desiredangle);  // writes the current value of int 'x' to the debug stream

	while(abs(SensorValue[gyro] - desiredangle) > 10)
	{
		//writeDebugStreamLine("c angle: %d", abs(SensorValue[gyro] - desiredangle));  // writes the current value of int 'x' to the debug stream

		//call the spin right function; pass (x1, x2, y2, duration)
		spinbot(speed,direction);

		//writeDebugStream("gyro value: %d", SensorValue[gyro]);  // writes the current value of int 'x' to the debug stream
	}
	//Call stop motors function after turning
	stopmotors();
}
void smoverobot(int xx1, int xx2, int yy1, int duration, int automode)
{
	if (automode==0)
	{
		motor[frontRight] = yy1 - xx2 - xx1;
		motor[backRight]  =  yy1 - xx2 + xx1;
		motor[frontLeft]  = yy1 + xx2 + xx1;
		motor[backLeft]   =  yy1 + xx2 - xx1;

	}
	//This section is for automous mode movement of the base
	if (automode==1)
	{
		motor[frontRight] = (yy1 - xx2 - xx1);
		motor[backRight]  =  (yy1 - xx2 + xx1);
		motor[frontLeft]  = (yy1 + xx2 + xx1);
		motor[backLeft]   =  (yy1 + xx2 - xx1);

		wait1Msec(duration);

		//Stop the robot
		stopmotors();
	}
}

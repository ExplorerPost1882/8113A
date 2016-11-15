#include "base.c"				 //main user code has all the voids...no need to modify.
#include "arm-test.c"

//pinchers
void pincers(string pos)
{
	int oppenP = 1000;
	if(pos == "oppen")
	{
		while ((abs(nMotorEncoder[pincer]) < (abs(oppenP)-30)))
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
	}
	if(pos == "closed")
	{

	}
}

//skiz atun
void win()
{
	moverobot(0,0,-700,0,1,medspd);
	wait1Msec (10);
	//movearm(medspd,0,1,3000);
	wait1Msec (1000);
	//start fetch loop
	for(int L=0;L < 4;L++)
	{
		moverobot(0,0,-1700,0,1,medspd);
		wait1Msec (10);
		//movearm(medspd,0,1,10000);
		wait1Msec (10);
		//movearm(medspd,0,1,10);
		wait1Msec (10);
		moverobot(0,0,1700,0,1,medspd);
		wait1Msec (10);
		if(SensorValue[gyro] < 0)
		{
			turnrobot(0,1,medspd);
			wait1Msec (10);
		}
		else if(SensorValue[gyro] > 0)
		{
			turnrobot(0,0,medspd);
			wait1Msec (10);
		}
		wait1Msec (1000);
	}
	//end fetch loop
	turnrobot(90,1,medspd-10);//turn tords west wall
	wait1Msec (10);
	moverobot(1000,0,0,0,1,medspd);//move sideways tords south wall
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//got tords west wall to get star
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//turn tords noth wall
	wait1Msec (10);
	moverobot(1000,0,0,0,1,medspd);//move sideways tords west wall
	wait1Msec (10);
	moverobot(0,0,5000,0,1,medspd);//go tords noth wall and pikup star 7
	wait1Msec (10);
	turnrobot(180,1,medspd-10);//rotate tords south wall
	wait1Msec (10);
	moverobot(0,0,-500,0,1,medspd);//back up to wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw 6&7 over wall and nock 8&9 off
	wait1Msec (10);
	turnrobot(90,0,medspd-10);//rotate tords east wall
	wait1Msec (10);
	moverobot(0,0,50000,0,1,medspd);//drive tored eats wall and get 10&11
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//rotate tords south wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw 10&11 over wall and nock 12&13 off
	wait1Msec (10);
	movearm(medspd,0,1,-10000);//lower arm
	wait1Msec (10);
	moverobot(0,0,5000,0,1,medspd);//drive tored  south wall and get cuba 3
	wait1Msec (10);
	moverobot(0,0,-5000,0,1,medspd);//drive tored  north wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw cuba 3 over wall
	wait1Msec (10);
	movearm(medspd,0,1,-10000);//lower arm
	wait1Msec (10);
	turnrobot(90,0,medspd-10);//rotate tords east wall
	wait1Msec (10);
	moverobot(0,0,500,0,1,medspd);//drive tored south east wall and get 14
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//rotate tords south wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw 14 over wall and nock 15 off
	wait1Msec (10);
	movearm(medspd,0,1,-10000);//lower arm
	wait1Msec (10);
	moverobot(100,0,0,0,1,medspd);//go sideways tords the west wall
	wait1Msec (10);
	moverobot(0,0,10000,0,1,medspd);//drive tored south east wall and get 16
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//rotate tords west wall
	wait1Msec (10);
	moverobot(100,0,0,0,1,medspd);//go sideways tords the south wall
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive tored west wall and get 17
	wait1Msec (10);
	moverobot(100,0,0,0,1,medspd);//go sideways tords the north wall
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//rotate tords south wall
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive tored north wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw 16&17 over wall and nock 18 off
	wait1Msec (10);
	movearm(medspd,0,1,-10000);//lower arm
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive tored south wall and get 19
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive tored north wall
	wait1Msec (10);
	moverobot(100,0,0,0,1,medspd);//go sideways tords the east wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw 19 over wall and nock 20 off
	wait1Msec (10);
	movearm(medspd,0,1,-10000);//lower arm
	wait1Msec (10);
	moverobot(100,0,0,0,1,medspd);//go sideways tords the east wall
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw rusha 4 over wall and nock 21 off
	wait1Msec (10);
	movearm(medspd,0,1,-10000);//lower arm
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//rotate tords east wall
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive east south wall and get 22
	wait1Msec (10);
	turnrobot(90,1,medspd-10);//rotate tords south wall
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive south south wall and get 23
	wait1Msec (10);
	moverobot(0,0,1000,0,1,medspd);//drive south south wall and get 23
	wait1Msec (10);
	movearm(medspd,0,1,10000);//throw 22 and 23 over wall and nock 24 off
	wait1Msec (10);
	//32
	for(int t = 0;t < 32; t++)
	{
		log(32);
	}
}

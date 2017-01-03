//88888888888888888888888888888    LCD READOUT  8888888888888888888888888888888888
task lcdAndArm()
{
	int xbat;
	string num;
	string number;
	//bat num
	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery;
	string armbattery;
	string armpos;
	string armTPos;
	string pncpos;
	string pncTPos;
	int mode = 1;
	int time = 5;

	while(1==1)
	{
		//888888888888888888888888888 START OF ARM OUTPUT 888888888888888888888888888
		if(armHol==1)
		{
			while ((nMotorEncoder[topRight] > (armTP+40)) || (nMotorEncoder[topRight] < (armTP-40)))
			{
				if (nMotorEncoder[topRight]<armTP) //if below selected point, move up toward it at "arm" speed
				{
					motor[topRight]     = armS;
					motor[bottomRight]  = armS;
					motor[topLeft]      = armS;
					motor[bottomLeft]   = armS;
					wait1Msec(80); //select for arm motion smoothness - too big a number will cause arm
					//to move too fast and shoot past mid point
				}
				else if (nMotorEncoder[topRight]>armTP) //if above selected point, move down toward it at "arm" speed
				{
					motor[topRight]     = -armS*2/3; //motion slowed when moving down to prevent overshoot
					motor[bottomRight]  = -armS*2/3;
					motor[topLeft]      = -armS*2/3;
					motor[bottomLeft]   = -armS*2/3;
					wait1Msec(10);
				}
				else // otherwise stop all arm motors
				{
					stoparm();
				}
			}
			stoparm();
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
			displayLCDString(0,0, "arm:");
			displayLCDString(1,0, "arm target:");
			sprintf(armpos, "%4.0f%c", nMotorEncoder[topRight]); //Build the value to be displayed
			sprintf(armTPos, "%4.0f%c", armTP); //Build the value to be displayed
			displayLCDString(0,4, armpos);
			displayLCDString(1,11, armTPos);
		}
		else if(mode == 4)
		{
			displayLCDString(0,0, "pinc:");
			displayLCDString(1,0, "pinc target:");
			sprintf(pncpos, "%4.0f%c", nMotorEncoder[pincerR]); //Build the value to be displayed
			sprintf(pncTPos, "%4.0f%c", pncTP); //Build the value to be displayed
			displayLCDString(0,4, pncpos);
			displayLCDString(1,11, pncTPos);
		}
		wait1Msec(time);
	}
}

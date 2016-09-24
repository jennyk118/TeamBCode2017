#pragma config(Sensor, dgtl1,  enc1,           sensorQuadEncoder)
#pragma config(Motor,  port2,           sanic,         tmotorVex269_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float Ks; //Scale factor for power to target speed conversion - see method powerToTargetSpeed
float Kp; //Constant for proportional portion of PID - rate of correction

int deltaAngularRotation() //Add option to read different encoders, then call for loop to cycle
{
	int deltaA = SensorValue[enc1];
	SensorValue[enc1] = 0;

	return deltaA;
}

float deltaTime()
{
	float deltaT = time1[timer1];
	clearTimer(timer1);

	return deltaT;
}

float velocity() //Velocity in angles per 20 ms - may need to increase time interval to be more accurate
{
	return ((float)deltaAngularRotation())/deltaTime();
}

float powerToTargetSpeed(int power) //Calculate the target speed based on the set power
{
	return (float)power*Ks; //Constant converts power to angles per 20 ms
}

int speedToPower(float speed)
{
	return (int)(speed/Ks); // Reverse conversion from powerToTargetSpeed
}

int correctedPIDPowerLevel(int powerLevel)
{
	float targetSpeed = powerToTargetSpeed(powerLevel);
	float actualSpeed = velocity();
	
	return speedToPower(targetSpeed-actualSpeed);
	
}

task main()
{
	while(true)
	{
		//writeDebugStreamLine("DeltaA: %i", deltaAngularRotation());
		motor[sanic] = correctePIDPowerLevel(127);
		wait1Msec(20);
	}
}

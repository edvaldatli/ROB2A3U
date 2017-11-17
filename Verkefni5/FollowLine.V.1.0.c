#pragma config(Sensor, in1,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)

int speed = 63;

task checkIfStopped()
{
	while(true){
		if(vexRT[Btn8U] == 1)
		{
			StopAllTasks();
		}
	}
}

task drive()
{
	int threshold = 2600;
	while(true)
	{
		if(SensorValue(lineFollowerRIGHT) > threshold)
		{
			motor[leftMotor]  = speed;
			motor[rightMotor] = 0;
		}
		if(SensorValue(lineFollowerCENTER) > threshold)
		{
			motor[leftMotor]  = speed;
			motor[rightMotor] = speed;
		}
		if(SensorValue(lineFollowerLEFT) > threshold)
		{
			motor[leftMotor]  = 0;
			motor[rightMotor] = speed;
		}
	}
}

task main()
{
	StartTask(checkIfStopped);
	StartTask(drive);
 	while(true){}
}

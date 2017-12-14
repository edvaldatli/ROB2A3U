#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder, encoder, encoderPort, dgtl1, 1000)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder, encoder, encoderPort, dgtl1, 1000)
#pragma config(Sensor, in8,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl6,  pushBtn,        sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Three projects in one project -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program combines three diffrent programs together so you can control them thru remote        *|
|*  You can abort the program anytime if you press 7U on the remote.																	*|
|*	You can stop the program you arre running anytime and start another one.													*|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions, line darkness, and surface lightness change from place to place,       *|
|*        so the value of 'threshold' may need to be changed to better suit your environment.         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*	  Sensor - Port 8	  lightSensor		  Sensor 				Top sensor  					  *|
|* 	  Sensor - Port 18 	  sonarSensor		  Sensor 				Front sensor
\*-----------------------------------------------------------------------------------------------4246-*/

//############################## 		ABORT		##########################//
task abort(){
	while(true){
		if(vexRT[Btn7U] == 1 || SensorValue[pushBtn] == 1){
			StopAllTasks();
		}
	}
}
//############################## 		ABORT		##########################//
//############################## VERKEFNI 1 ##########################//
void moveForward(int time){
			motor[rightMotor] = 127;
			motor[leftMotor] = 127;
			wait1Msec(time);
			motor[rightMotor] = 0;
			motor[leftMotor] = 0;
		}
void moveBackwards(int time){
			motor[rightMotor] = -127;
			motor[leftMotor] = -127;
			wait1Msec(time);
			motor[rightMotor] = 0;
			motor[leftMotor] = 0;
}

task verkefni1(){
		int BASEVALUE = 0;

		wait1Msec(1000);
		for (BASEVALUE; BASEVALUE <= 4500; BASEVALUE += 900){
				moveForward(BASEVALUE);wait1Msec(1000);
				moveBackwards(BASEVALUE);wait1Msec(1000);
		}
}
//############################## VERKEFNI 1 ##########################//
//############################## VERKEFNI 2 ##########################//
void driveForward(int dist)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	while(SensorValue[leftEncoder] < dist){

		if(SensorValue[rightEncoder] == SensorValue[leftEncoder]){
			motor[rightMotor] = 127;
			motor[leftMotor]  = 127;
		}
		else if(SensorValue[rightEncoder] > SensorValue[leftEncoder]){
			motor[rightMotor] = 107;
			motor[leftMotor]  = 127;
		}
		else{
			motor[rightMotor] = 127;
			motor[leftMotor]  = 107;
		}
	}
}

void stopMotors(){
	motor[rightMotor] = 0;
  motor[leftMotor] = 0;
  wait1Msec(800);
};

void turn90Degrees(int left,int right){
	motor[leftMotor] = left;
  motor[rightMotor] = right;
  wait1Msec(523);
}

task verkefni2(){
	const int dist = 580;

	driveForward(dist);
	stopMotors();

	turn90Degrees(-127,127);
	stopMotors();

	for (int i = 1; i <= 2; i++){
		driveForward(dist);
		stopMotors();
		turn90Degrees(70,-127);
		stopMotors();
	}

	driveForward(dist);
	stopMotors();
}
//############################## VERKEFNI 2 ##########################//
//############################## VERKEFNI 3 ##########################//

task stopAllMotors(){
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
}

task verkefni3(){
	while(true){
		if(SensorValue(sonarSensor) < 55 || SensorValue(sonarSensor) == -1 ){
      motor[rightMotor] = -60;
      motor[leftMotor] = 60;
      wait1Msec(535);
    }else if(SensorValue(lightSensor) > 300){
    	StartTask(stopAllMotors);
  	}
  	else{
    	motor[rightMotor] = 127;
    	motor[leftMotor] = 127;
  	}
	}
}
//############################## VERKEFNI 3 ##########################//
//############################## STOP TASKS ##########################//

task stopTasks(){
	while(true){
		if(vexRT[Btn7L] == 1){
			StopTask(verkefni1);
			StopTask(verkefni2);
			StopTask(verkefni3);
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
		}
	}
}
//############################## STOP TASKS ##########################//
//############################## 		MAIN		##########################//
task main()
{
	StartTask(abort);
	StartTask(stopTasks);
	while(true){
		if(vexRT[Btn8U] == 1){
			StartTask(verkefni1);
		}else if(vexRT[Btn8R] == 1){
			StartTask(verkefni2);
		}else if(vexRT[Btn8L] == 1){
			StartTask(verkefni3);
		}
	}
}
//############################## 		MAIN		##########################//

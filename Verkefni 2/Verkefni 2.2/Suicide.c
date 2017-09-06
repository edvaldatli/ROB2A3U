#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)

int BASEVALUE = 540;

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

task main()
{
  wait1Msec(2000);

    //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;

  for (BASEVALUE; SensorValue[leftEncoder] < 2700; BASEVALUE += BASEVALUE){
    moveForward(BASEVALUE);wait1Msec(1000);
    moveBackwards(BASEVALUE);wait1Msec(1000);
  }

}

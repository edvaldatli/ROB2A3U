while(Btn7u && pushBtn == 0)
{
  driveForward()
  if(SonarSkynjarHættu)
  {
    left,right motor = 0
    left,right motor -127
    Bíða í 200ms
    right motor = 127
    left motor = -127
  }
}

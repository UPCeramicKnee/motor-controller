/* Quickstop Program
John Saunders NYCCNC http://www.nyccnc.com/

microstep driver ST-M5045
Pul+ goes to +5V
Pul- goes to Arduino Pin 22 (was 9)
Dir+ goes to +5V
Dir- goes to to Arduino Pin 24 (was 8)
Enable+ to nothing
Enable- to nothing
*/

#include "AccelStepper.h"

// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER,22,24); 

void setup()
{  
  //Serial.begin(9600);
  stepper.setMaxSpeed(3000); //we want 150*128, but max supported is about 4000
  stepper.setAcceleration(10000);
}

void loop(){
  for(int i=0;i<10;i++){
    stepper.runToNewPosition(264);
    stepper.runToNewPosition(0);
  }
  delay(10000);
}


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
  stepper.setMaxSpeed(4000); //we want 150*128, but max supported is about 4000
  stepper.setAcceleration(3000);
}

void loop(){    
  //total microsteps in rev: 3200
  stepper.moveTo(3200);
  while (stepper.currentPosition() != 1600) // Full speed up to 250000
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  delay(10000);
  // Now stopped after quickstop

  // Now go backwards
  stepper.moveTo(-3200);
  while (stepper.currentPosition() != 0) // Full speed basck to 0
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop
}


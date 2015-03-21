/* Quickstop Program
John Saunders NYCCNC http://www.nyccnc.com/

microstep driver ST-M5045
Pul+ goes to +5V
Pul- goes to Arduino Pin 9
Dir+ goes to +5V
Dir- goes to to Arduino Pin 8
Enable+ to nothing
Enable- to nothing
*/

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(1,8,9); 

void setup()
{  
  stepper.setMaxSpeed(150);
  stepper.setAcceleration(100);
}

void loop(){    
stepper.moveTo(500);
  while (stepper.currentPosition() != 300) // Full speed up to 300
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop

  // Now go backwards
  stepper.moveTo(-500);
  while (stepper.currentPosition() != 0) // Full speed basck to 0
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop
}


// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to 
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
#include <MultiStepper.h>
#include "PinsAndConfiguration.h"
#include "AccelStepperDecorate.h"


AccelStepper stepper1(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
//AccelStepper stepper2(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);

/*
    AccelStepperDecorate(char motorName,
                         int dirPin,
                         int stepPin,
                         int enablePin,

                         int outRangePinNegative,
                         int outRangePinPositive,
                         bool outRangeSwitch,

                         int subdivision,
                         int reductionRatio,
                         double stepAngle,
                         double maxSpeed,
                         double acceleration,
                         double maxMovingDistance,
                         
                         double disPerRound
                         );
*/

AccelStepperDecorate stepper2Decorate('Y',
                     Y_DIR_PIN,
                     Y_STEP_PIN,
                     Y_ENABLE_PIN,

                     0 ,
                     0 ,
                     false ,

                     1 ,
                     1 ,
                     1.8 ,
                     200 ,
                     50 ,
                     20 ,
                     
                     0.1
                     );



// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

void setup() {
  Serial.begin(9600);

  stepper1.setPinsInverted(false, false, true);
  stepper1.setEnablePin(X_ENABLE_PIN);
//  stepper2.setPinsInverted(false, false, true);
//  stepper2.setEnablePin(Y_ENABLE_PIN);

  // Configure each stepper
//  stepper1.setMaxSpeed(300);
//  stepper2.setMaxSpeed(300);

  stepper1.setAcceleration(50.0);
//  stepper2.setAcceleration(50.0);

  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
//  steppers.addStepper(stepper2);
  steppers.addStepper(stepper2Decorate.stepper);

  int maxspeed[2] = {300, 300};
  steppers.moveRelativeWithAccelSetbackMaxSpeed(maxspeed);
}


/**
 * Suggest usage
 */
void loop() {
  long relative[2]; // Array of desired stepper positions
  
  relative[0] = 2000;
  relative[1] = 1000;
  steppers.moveRelativeWithPredefinedAccel(relative);
  steppers.runAccelToPosition(); // Blocks until all are in position
  delay(10000);
  
  // Move to a different coordinate
  relative[0] = -1000;
  relative[1] = -1000;
//  steppers.moveTo(relative);
//  steppers.runSpeedToPosition(); // Blocks until all are in position
  steppers.moveRelativeWithPredefinedAccel(relative);
  steppers.runAccelToPosition(); // Blocks until all are in position
  delay(1000);
}

/*
void loop() {

  int maxspeed[2] = {300, 300};
  
  long relative[2]; // Array of desired stepper positions
  
  relative[0] = 1000;
  relative[1] = 2000;
  steppers.moveRelativeWithAccel(relative);
  steppers.runAccelToPosition(); // Blocks until all are in position
  steppers.moveRelativeWithAccelSetbackMaxSpeed(maxspeed);
  delay(1000);
  
  // Move to a different coordinate
  relative[0] = -1000;
  relative[1] = -100;
  steppers.moveRelativeWithAccel(relative);
  steppers.runAccelToPosition(); // Blocks until all are in position
  steppers.moveRelativeWithAccelSetbackMaxSpeed(maxspeed);
  delay(1000);
}
*/





/*
void loop() {
  long positions[2]; // Array of desired stepper positions
  
  positions[0] = 1000;
  positions[1] = 50;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
  
  // Move to a different coordinate
  positions[0] = -100;
  positions[1] = 100;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}*/

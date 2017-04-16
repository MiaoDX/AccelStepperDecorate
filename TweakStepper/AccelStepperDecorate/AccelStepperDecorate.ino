// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
// #include <MultiStepper.h>
#include "PinsAndConfiguration.h"
#include "AccelStepperDecorate.h"
#include "MultiStepperDecorate.h"


// AccelStepper stepper1(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
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

AccelStepperDecorate stepper1Decorate('X',
                                      X_DIR_PIN,
                                      X_STEP_PIN,
                                      X_ENABLE_PIN,

                                      X_MIN_PIN,
                                      X_MAX_PIN,
                                      false,

                                      1 ,
                                      1 ,
                                      1.8 ,
                                      200 ,
                                      50 ,
                                      20 ,

                                      0.1
                                     );

AccelStepperDecorate stepper2Decorate('Y',
                                      Y_DIR_PIN,
                                      Y_STEP_PIN,
                                      Y_ENABLE_PIN,

                                      Y_MIN_PIN,
                                      Y_MAX_PIN,
                                      false,


                                      32 ,
                                      1 ,
                                      1.8 ,
                                      200 ,
                                      50 ,
                                      20 ,

                                      0.1
                                     );



// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepperDecorate steppersDecorate;


void setup() {
  Serial.begin(9600);

  // Then give them to MultiStepper to manage
  steppersDecorate.addStepper(stepper1Decorate);
  steppersDecorate.addStepper(stepper2Decorate);
}


void loop() {

  long relative[2] = {2000, -1000*32};
  steppersDecorate.moveRelativeWithPredefinedAccel(relative);
  steppersDecorate.prepareToGo();
  steppersDecorate.runAccelToPosition();

  delay(2000);
}


/*
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



  void loop() {

  stepper1.disableOutputs();

  stepper2Decorate.stepper.move(1000);
  stepper2Decorate.prepareToGo();

  //  while (abs(stepper2Decorate.stepper.distanceToGo()) > 0) {
  //    stepper2Decorate.run();
  //  }

  while (stepper2Decorate.run())
    ;



  delay(2000);


  long steps = stepper2Decorate.dis2Pulses(-1.0);

  stepper2Decorate.stepper.move(steps);
  stepper2Decorate.prepareToGo();
  //  while (abs(stepper2Decorate.stepper.distanceToGo()) > 0) {
  //    stepper2Decorate.run();
  //  }

  while (stepper2Decorate.run())
    ;

  delay(2000);

  }
*/



/**
   Suggest usage
*/
/*
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
*/


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

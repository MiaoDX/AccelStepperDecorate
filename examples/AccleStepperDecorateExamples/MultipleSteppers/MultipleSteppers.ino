// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Use MultiStepperDecorate class to manage multiple steppers and make them all move to
// different positions at predefined speed.

#include <AccelStepper.h>
// #include <MultiStepper.h>
#include <PinsAndConfiguration.h>
#include <AccelStepperDecorate.h>
#include <multiStepperDecorate.h>


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

  // pay attention to the different subdivision of the two steppers, first one with no subdivision, the second one have a subdivision of 32.

  long relative[2] = {2000, -1000*32};
  steppersDecorate.moveRelativeWithPredefinedAccel(relative);
  steppersDecorate.prepareToGo();
  steppersDecorate.runAccelToPosition();

  delay(2000);
}
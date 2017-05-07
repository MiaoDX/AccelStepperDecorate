// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Make a single stepper some relative steps from one limit to another
// 
// This is just a minimum stepper to show how the AccelStepperDecorate Library work.

#include <AccelStepper.h>
#include <PinsAndConfiguration.h>
#include <AccelStepperDecorate.h>


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

/*
* Note that this stepper is hard coded enable pin as reversed
* so if your shield or board connection won't run at all, just check this
*
* The Limit pins (MIN_PIN and MAX_PIN) are set to be unset (outRangeSwitch == false), so don't have to do extra wire connection.
* and thus the maxMovingDistance is also useless.
*
* The subdivision is set to 1 (no subdivision)
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
                                      400 ,
                                      50 ,
                                      -1 ,

                                      0.1
                                     );


void setup() {
  Serial.begin(9600);
}



void loop() {

  long relative = 200*40L;

  stepper1Decorate.stepper.move(relative); // this is really ugly.

  stepper1Decorate.prepareToGo();

  // wait to finish the run
  while (stepper1Decorate.run())
	; // idle wait

  stepper1Decorate.stop();


  delay(2000);
}
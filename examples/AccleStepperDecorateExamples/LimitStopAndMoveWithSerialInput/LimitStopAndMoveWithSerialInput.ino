// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Make a single stepper some relative steps from one limit to another, the limit is controlled by the limit pins


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
* The Limit pins (MIN_PIN and MAX_PIN) are set to be used (outRangeSwitch == true), so we need to do some wire connection to make 
* this experiment work.

The limit pins emit `LOW` means the stepper have encountered the limit and should stop, so if we want to make the stepper run, we 
set the limit `HIGH`, if we want it stop, set it `LOW` is enough.

A very easy way to check this is use a switch button and click to check the function.


*
* We do not use maxMovingDistance now so set it to -1 is ok.
*
* The subdivision is set to 1 (no subdivision)
*/
AccelStepperDecorate stepper1Decorate('X',
                                      X_DIR_PIN,
                                      X_STEP_PIN,
                                      X_ENABLE_PIN,

                                      X_MIN_PIN, // 3
                                      X_MAX_PIN, // 
                                      true,

                                      32 ,
                                      1 ,
                                      1.8 ,
                                      200 ,
                                      50 ,
                                      -1 ,

                                      0.1
                                     );

void setup() {
  Serial.begin(9600);
}


void loop() {

  long relative = 0;

  Serial.println("IDEL waiting command...");
  while (!Serial.available()){
    ;
  }

  while (Serial.available()) {
    relative = 200 * 2 * 32L; // this is relatively large, just to test whether the limit funtion is usable.
    char inChar = Serial.read();
    switch (inChar) {  // read a character
        Serial.print("WE GOT FROM SERIAL: ");
        Serial.print(inChar);
        case '0':   
          relative = 0;
          break;
        case '1':
          relative = relative;
          break;
        case '2':
          relative = -relative;
          break;
        default:  // all other commands are ignored.
          Serial.println("Bad Command");
      }

	while (Serial.read() >= 0)
		; // flush any extra characters
  }


  Serial.println("Going to run!");


  check_now_min_max_value();

  stepper1Decorate.prepareToGo();

  stepper1Decorate.stepper.move(relative); // this is really ugly.  


  long dsTG = stepper1Decorate.stepper.distanceToGo();
  Serial.print("distance to go:");
  Serial.println(dsTG);

  // wait to finish the run
  while (stepper1Decorate.run()) {
	  ; // idle wait
	  if (stepper1Decorate.stepper.distanceToGo() % 1000 == 0) {
		  Serial.println("still going");
	  }
  }
	
  stepper1Decorate.stop();

  dsTG = stepper1Decorate.stepper.distanceToGo();
  Serial.print("distance to go:");
  Serial.println(dsTG);
  check_running_status();
  

  delay(2000);
}

void check_now_min_max_value() {
	int min_v = digitalRead(X_MIN_PIN);
	int max_v = digitalRead(X_MAX_PIN);
	Serial.println("min_v and max_v are:");
	Serial.print(min_v);
	Serial.print(" ");
	Serial.println(max_v);
}

void check_running_status() {
	// let's check the results
	int status = stepper1Decorate.rangeStatus();
	Serial.print("the stauts of this moving is: ");
	Serial.println(status);
	if (status == -1) {
		Serial.println("Seem encounter the negative limit");
	}
	else if (status == 1) {
		Serial.println("Seem encounter the positive limit");
	}
	else {
		Serial.println("All seems nice");
	}
}
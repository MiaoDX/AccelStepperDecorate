// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Make a single stepper HOMING, the limit is controlled by the limit pins


#include <AccelStepper.h>
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

/*
* Note that this stepper is hard coded enable pin as reversed
* so if your shield or board connection won't run at all, just check this
*
* The Limit pins (MIN_PIN and MAX_PIN) are set to be used (outRangeSwitch == true), so we need to do some wire connection to make
* this experiment work.

The limit pins emit `LOW` means the stepper have encountered the limit and should stop, so if we want to make the stepper run, we
set the limit `HIGH`, if we want it stop, set it `LOW` is enough.

A very easy way to check this is use a switch button and click to check the function.

We are testing HOMING, so maxMovingDistance should be set

* The subdivision is set to 32.
*/
AccelStepperDecorate stepper1Decorate('X',
	X_DIR_PIN,
	X_STEP_PIN,
	X_ENABLE_PIN,

	X_MIN_PIN, // 3
	X_MAX_PIN, // 2
	true,

	32,
	1,
	1.8,
	200,
	50,
	X_MAX_MovingDistance,

	X_disPerRound
);
MultiStepperDecorate steppersDecorate;

void setup() {
	Serial.begin(9600);

	steppersDecorate.addStepper(stepper1Decorate);
}



void loop() {
	check_now_min_max_value();

	int rtn = steppersDecorate.homing();
	Serial.print("The result of homing is:");
	Serial.println(rtn);

	long dsTG = stepper1Decorate.stepper.distanceToGo();
	Serial.print("distance to go:");
	Serial.println(dsTG);
	check_running_status();

	Serial.println("All done for one moving");
	delay(5000);
}

void check_now_min_max_value() {
	Serial.println("min_v and max_v are:");
	for (int i = 0; i < 20; i++) {

		int min_v = digitalRead(X_MIN_PIN);
		int max_v = digitalRead(X_MAX_PIN);

		Serial.print("X_MIN_PIN,");
		Serial.print(X_MIN_PIN);
		Serial.print(":");
		Serial.print(min_v);
		Serial.print("  ");
		Serial.print("X_MAX_PIN,");
		Serial.print(X_MAX_PIN);
		Serial.print(":");
		Serial.println(max_v);
	}
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
// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Use MultiStepperDecorate class to manage multiple steppers and make them all move to
// different positions at predefined speed. And check the limit stop option.

// The only difference with `MultipleSteppersDistanceTranslation` is that, we make the steppers' limit pin enable.

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

AccelStepperDecorate stepper1Decorate('X',
	X_DIR_PIN,
	X_STEP_PIN,
	X_ENABLE_PIN,

	X_MIN_PIN,
	X_MAX_PIN,
	true,

	32,
	1,
	1.8,
	200,
	50,
	X_MAX_MovingDistance,

	X_disPerRound
);

AccelStepperDecorate stepper2Decorate('Z',
	Z_DIR_PIN,
	Z_STEP_PIN,
	Z_ENABLE_PIN,

	Z_MIN_PIN,
	Z_MAX_PIN,
	true,

	32,
	1,
	1.8,
	400,
	50,
	Z_MAX_MovingDistance,

	Z_disPerRound
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

	double relativeDistance[2] = { 10.0, 0 };
	steppersDecorate.moveRelativeDistancesWithPredefinedAccel(relativeDistance);

	int rangeStatusArr[2];
	steppersDecorate.getAndReportAllRangeStatus(rangeStatusArr);

	delay(2000); //- running done, first stepper status {rangeStatusArr[0]}, second stepper status {rangeStatusArr[1]}
}
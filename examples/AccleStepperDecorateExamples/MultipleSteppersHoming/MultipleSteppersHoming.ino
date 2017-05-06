// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Use MultiStepperDecorate class to manage multiple steppers and test their homing funciton.

// Since we want to test homing funciton, we make the steppers' limit stop pin enable.

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

	1,
	1,
	1.8,
	200,
	50,
	2,

	0.1
);

AccelStepperDecorate stepper2Decorate('Y',
	Y_DIR_PIN,
	Y_STEP_PIN,
	Y_ENABLE_PIN,

	Y_MIN_PIN,
	Y_MAX_PIN,
	false,


	32,
	1,
	1.8,
	200,
	50,
	20,

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

	//- For debug,  {@ReportDigital}

	/*
	To test homing function, the test case can be:

	0)Make steppers without LIMIT, so will just return, and homingRtn will be 1.
	1)First is to make all limit pin HIGH to make the homing function fail when approaching LIMIT
	2)Second is to make the moving distance (a.k.a maxMovingDistance of the stepper) large enough so that we can control the LIMIT pin value as needed to check the function,
		to be more concrete, when the stepper is approaching LIMIT, we can make the pin HIGH and the it will move backword for half maxMovingDistance


	Really situation)Second is conncet wire to the real platfrom with LIMIT pins connected as see all things OK
	*/
	
	/* 
	To test this function, we'd better have a switch to make things easy, now is just plug the wire in and out -.-
	*/


	// pay attention to the different subdivision of the two steppers, first one with no subdivision, the second one have a subdivision of 32.

	/* 
	LET us do some calculation,
	1) first stepper, no subdivision, maxMovingDistance=2cm, disPerRound=0.1cm, so maxMovingSteps=2/0.1*200 = 4,000
	2) second stepper, subdivision of 32, maxMovingDistance=20cm, disPerRound=0.1cm, so maxMovingSteps=20/0.1*200*32 = 40,000*32 = 1,280,000
	*/

	int homingRtn = steppersDecorate.homing();

	int rangeStatusArr[2];
	steppersDecorate.getAndReportAllRangeStatus(rangeStatusArr);

	delay(2000); //- running done, homingRtn is: {homingRtn} , first stepper status {rangeStatusArr[0]}, second stepper status {rangeStatusArr[1]}
}
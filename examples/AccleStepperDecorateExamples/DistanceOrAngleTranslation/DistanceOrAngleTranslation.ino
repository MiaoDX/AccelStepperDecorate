// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Make a single stepper some relative steps from one limit to another
// Test the function of distance translation


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
* The subdivision is set to 32
*/
AccelStepperDecorate stepper1Decorate('X',
	X_DIR_PIN,
	X_STEP_PIN,
	X_ENABLE_PIN,

	X_MIN_PIN,
	X_MAX_PIN,
	true,

	20,
	1,
	1.8,
	200,
	50,
	-1,

	0.1
);

void setup() {
	Serial.begin(9600);
}


void loop() {

	double relativeCM = 20;

	long relativeSteps = stepper1Decorate.dis2Pulses(relativeCM); // the answer should == relativeDis/disPerRound * stepsPerRound = 2/0.1 * (200*20) = 20* 4000 = 80,000

	stepper1Decorate.prepareToGo();

	stepper1Decorate.stepper.move(relativeSteps); // this is really ugly.

	

	// wait to finish the run
	while (stepper1Decorate.run())
		; // idle wait

	stepper1Decorate.stop();


	delay(2000);
}
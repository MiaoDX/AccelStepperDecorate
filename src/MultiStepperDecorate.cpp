// MultiStepperDecorate.cpp
//
// Copyright (C) 2015 Mike McCauley
// $Id:  $

#include "MultiStepperDecorate.h"

MultiStepperDecorate::MultiStepperDecorate()
    : _num_steppers(0)
{
}

boolean MultiStepperDecorate::addStepper(AccelStepperDecorate &stepper)
{
    if (_num_steppers >= MULTISTEPPER_MAX_STEPPERS)
	return false; // No room for more
    _steppers_decorate[_num_steppers++] = &stepper;
}



void MultiStepperDecorate::moveRelativeDistancesWithPredefinedAccel(double relativeDistance[])
{
    long maxMovingSteps[_num_steppers]; // have not init

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
        maxMovingSteps[i] = _steppers_decorate[i]->dis2Pulses(relativeDistance[i]);
    }

    Serial.println("the steps calculated from distances are:");
    repoertArray(maxMovingSteps);

    moveRelativeStepsWithPredefinedAccel(maxMovingSteps);
    

    // int rangeStatusArr[_num_steppers];
    // getAndReportAllRangeStatus(rangeStatusArr);
}

void MultiStepperDecorate::repoertArray(long arr[])
{
	uint8_t i;
	for (i = 0; i < _num_steppers; i++)
	{
		Serial.print(arr[i]); Serial.print(" ");
	}
	Serial.println();
}


/**
  NOTE: must specify the accel at setup

  Very like the original moveTo, just use predefined accelerate, the cons is that, the steppers stop time will be no relational
  which is acceptable for our usage.
*/
void MultiStepperDecorate::moveRelativeStepsWithPredefinedAccel(long relative[])
{

    prepareToGo(); // we call prepareToGo at the very beginning

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->stepper.move(relative[i]); // New target position (without new speed reset, thus use predefined speed)
    }


    
    runAccelToPosition();

    // int rangeStatusArr[_num_steppers];
    // getAndReportAllRangeStatus(rangeStatusArr);
}



void MultiStepperDecorate::prepareToGo()
{
    uint8_t i;

    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->prepareToGo(); // New target position (without speed reset)
    }
}

// Returns true if any motor is still running to the target position.
boolean MultiStepperDecorate::runAccel()
{
    uint8_t i;
    boolean ret = false;
    for (i = 0; i < _num_steppers; i++)
    {
        bool now_stepper_state = _steppers_decorate[i]->run();

        if(now_stepper_state == false){ // either reach the limit or run all required steps, to avoid some steppers run much longer time and let others hot, just stop the stopped ones
            _steppers_decorate[i]->stop();
        }

	   ret = now_stepper_state || ret;
    }
    return ret;
}

// Blocks until all steppers reach their target position and are stopped
void MultiStepperDecorate::runAccelToPosition()
{
    while (runAccel())
	;
}

void MultiStepperDecorate::getAndReportAllRangeStatus(int rangeStatusArr[])
{
    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
	rangeStatusArr[i] = _steppers_decorate[i]->rangeStatus();
    }


    Serial.println("the running status of steppers after this move are:");
    for (i = 0; i < _num_steppers; i++)
    {
    Serial.print(rangeStatusArr[i]);
    }
    Serial.println();
}


int MultiStepperDecorate::homing()
{

    bool rtn = false;
    bool limit_flag;
    
    long maxMovingSteps[_num_steppers]; // have not init

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
        maxMovingSteps[i] = 0L; // just init
    
        limit_flag = _steppers_decorate[i]->outRangeSwitch;
        if(limit_flag){ // update move steps if limit set
            maxMovingSteps[i] = _steppers_decorate[i]->dis2Pulses(_steppers_decorate[i]->maxMovingDistance *2);// pay attention to the multiply 2, we use this to make sure will get the limit
        }

        Serial.println("calculated maxMovingSteps (times 2 to make sure limit will be reached)");
        repoertArray(maxMovingSteps);

        rtn = rtn || limit_flag;
    }

    // if all steppers are no-limit stepper, just return
    if (rtn == false){
        return 1; // hard-coded return value for no need to move
    }

    // move the calculated steps

    moveRelativeStepsWithPredefinedAccel(maxMovingSteps);
    
    int rangeStatusArr[_num_steppers];
    getAndReportAllRangeStatus(rangeStatusArr);

    // make sure got limit stop
    for (i = 0; i < _num_steppers; i++)
    {    
        limit_flag = _steppers_decorate[i]->outRangeSwitch;
        if(limit_flag && _steppers_decorate[i]->rangeStatus() != 1){ // check the got the limit
            return -1;  // we encounter an error since the limit did not show up as expected
        }
    }

    // reset move steps for homing
    for (i = 0; i < _num_steppers; i++)
    {
        maxMovingSteps[i] /= -4; // we multiply it by 2 just now
    }

    Serial.println("calculated movingSteps for homing (maxMovingSteps/2 for homing)");
    repoertArray(maxMovingSteps);

    moveRelativeStepsWithPredefinedAccel(maxMovingSteps);
    getAndReportAllRangeStatus(rangeStatusArr);

    // make sure got limit stop
    for (i = 0; i < _num_steppers; i++)
    {   
        if(rangeStatusArr[i] != 0){
            return -2; // this will not happen, since we only move half distance
        }
    }

    return 0;
} 
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


/**
  NOTE: must specify the accel at setup

  Very like the original moveTo, just use predefined accelerate, the cons is that, the steppers stop time will be no relational
  which is acceptable for our usage.
*/
void MultiStepperDecorate::moveRelativeWithPredefinedAccel(long relative[])
{
    // First find the stepper that will take the longest time to move
    float longestTime = 0.0;

    uint8_t i;

    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->stepper.move(relative[i]); // New target position (without speed reset)
    }

    /* enable pins to move */
    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->stepper.enableOutputs();
    }
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
	ret = _steppers_decorate[i]->run() || ret; // if there are steppers have not stoped, just keep running, pay ATTENTION TO THE ORDER
    }
    return ret;
}

// Blocks until all steppers reach their target position and are stopped
void MultiStepperDecorate::runAccelToPosition()
{
    while (runAccel())
	;

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->stop();
    }
}

void MultiStepperDecorate::getAllRangeStatus(int rangeStatusArr[])
{
    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
	rangeStatusArr[i] = _steppers_decorate[i]->rangeStatus();
    }
}

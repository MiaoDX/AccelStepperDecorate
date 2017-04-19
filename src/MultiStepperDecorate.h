// MultiStepperDecorate.h

#ifndef MultiStepperDecorate_h
#define MultiStepperDecorate_h

#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#define MULTISTEPPER_MAX_STEPPERS 10

#include "AccelStepperDecorate.h"

//class AccelStepperDecorate;

/*
  MultiStepperDecorate, change from `MultiStepper`, to support StepperDecorate and make things easier to NOT
  make a liner run, just a predefined maxspeed and accelerate
*/

class MultiStepperDecorate
{
  public:
    /// Constructor
    MultiStepperDecorate();

    /// Add a stepper to the set of managed steppers
    /// There is an upper limit of MULTISTEPPER_MAX_STEPPERS = 10 to the number of steppers that can be managed
    /// \param[in] stepper Reference to a stepper to add to the managed list
    /// \return true if successful. false if the number of managed steppers would exceed MULTISTEPPER_MAX_STEPPERS
    boolean addStepper(AccelStepperDecorate &stepperDecorate);

    void moveRelativeWithAccel(long relative[]);

    void moveRelativeWithAccelSetbackMaxSpeed(int maxspeed[]);

    void moveRelativeWithPredefinedAccel(long relative[]);

    void prepareToGo();

    boolean runAccel();

    void runAccelToPosition();

    void getAllRangeStatus(int rangeStatusArr[]);

  private:
    /// Array of pointers to the steppers we are controlling.
    /// Fills from 0 onwards
    AccelStepperDecorate *_steppers_decorate[MULTISTEPPER_MAX_STEPPERS];

    /// Number of steppers we are controlling and the number
    /// of steppers in _steppers[]
    uint8_t _num_steppers;
};

/// @example MultiStepper.pde
/// Use MultiStepper class to manage multiple steppers and make them all move to
/// the same position at the same time for linear 2d (or 3d) motion.

#endif

// Quickstop.pde
// -*- mode: C++ -*-
//
// Check stop handling.
// Calls stop() while the stepper is travelling at full speed, causing
// the stepper to stop as quickly as possible, within the constraints of the
// current acceleration.
//
// Copyright (C) 2012 Mike McCauley
// $Id:  $

#include <AccelStepper.h>

// For RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
//#define X_MIN_PIN           3
//#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

AccelStepper stepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);


void setup()
{   
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);
  stepper.setMaxSpeed(300);
  stepper.setAcceleration(100);
  //stepper.setCurrentPosition(0);
}

void loop()
{    
  stepper.moveTo(2000);
  while (stepper.speed() != 300) // Full speed up to 300
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop

/*
  // Now go backwards
  stepper.moveTo(-2000);
  while (stepper.speed() != 300) // Full speed basck to 0
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop
*/
}


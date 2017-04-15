// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define a stepper and the pins it will use
// For RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
//#define X_MIN_PIN           3
//#define X_MAX_PIN           2
AccelStepper stepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

/*
void setup() 
{  
  stepper.setEnablePin(X_ENABLE_PIN);
}

void loop()
{
    if (stepper.distanceToGo() == 0)
    {
  // Random change to speed, position and acceleration
  // Make sure we dont get 0 speed or accelerations
  delay(1000);
  stepper.moveTo(rand() % 200);
  stepper.setMaxSpeed((rand() % 200) + 1);
  stepper.setAcceleration((rand() % 200) + 1);
    }
    stepper.run();
}
*/






void setup()
{  
//  pinMode(X_ENABLE_PIN, OUTPUT);
//  digitalWrite(X_ENABLE_PIN, LOW);

  stepper.setPinsInverted(false, false, true);
  stepper.setEnablePin(X_ENABLE_PIN);
  


  stepper.setMaxSpeed(300);
  stepper.setAcceleration(50);
}

void loop()
{    
  stepper.moveTo(800);
//  while (stepper.distanceToGo() != 0) // Full speed up to 300
//    stepper.run();
//  stepper.runToNewPosition(0);
//
//  stepper.move(800);
  stepper.runToPosition();
  stepper.disableOutputs();
//  //stepper.runToNewPosition(); // Cause an overshoot then back to 0
//  while (stepper.currentPosition() != 800) // Full speed up to 300
//    stepper.run();

  
}





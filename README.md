# Arduino Stuff

We list some arduino code for our platform controlling.

## Tweak the steppers (aka AccelStepperDecorate and MultiStepperDecorate).

We wrap and extend [`AccelStepper`](http://www.airspayce.com/mikem/arduino/AccelStepper) to provide more useful functions for our platform.

### Usage

1.Download the `AccelStepper` lib

`Sketch -> Include Library -> Manage Libraries`

Search `AccelStepper` and download. It should be in `C:\Users\<Your-User-Name>\Documents\Arduino\libraries` folder.

2.Clone and try the codes (.ino) we provide. (Will make a lib after organize the code)


### TODO

Communicate with outside.



## Some tips to use [`AccelStepper`](http://www.airspayce.com/mikem/arduino/AccelStepper):

### Use Driver version stepper

``` cpp
// For RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
//#define X_MIN_PIN           3
//#define X_MAX_PIN           2
AccelStepper stepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
```


### Use `ENABLE_PIN`

``` cpp
  stepper.setPinsInverted(false, false, true); // possibly inverted pin(this is true for rasp board)
  stepper.setEnablePin(X_ENABLE_PIN);
```

### Disable pins to save energy and avoid stepper being too hot

``` cpp
  stepper.moveTo(800);
  stepper.runToPosition();
  stepper.disableOutputs();
```

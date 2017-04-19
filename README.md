ATTENTION! This library is still under heavy development, and to be honest, I make it a library just to test the functions more convenient (we can have more that one example to use the source code)

I will put more examples and design principle latter (hope won't be too long).

# AccelStepperDecorate

We wrap and extend [`AccelStepper`](http://www.airspayce.com/mikem/arduino/AccelStepper) to provide more useful functions for our platform, aka `AccelStepperDecorate` and `MultiStepperDecorate`.

### Usage

1.Download the original `AccelStepper` lib

`Sketch -> Include Library -> Manage Libraries`

Search `AccelStepper` and download. It should be in `C:\Users\<Your-User-Name>\Documents\Arduino\libraries` folder.

2.Clone and try the examples we provide and make sure put it in the `libraries` folder.

``` vi
pwd
# C:\Users\<Your-User-Name>\Documents\Arduino\libraries
git clone https://github.com/MiaoDX/AccelStepperDecorate.git
```


### TODO

* More examples
* Communicate with outside for a more usable perspective
* Documents

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



# Update

20170419, We made it a library!
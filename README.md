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


## Lesson Learned

### Stop pin

We are using `digitalRead` to read a analog sensor (the Hall element), it's ugly but doable.

If the sensor reach `LOW`, then it will always emits `LOW` signal, otherwise, it will emits a wave, so it won't always be `LOW`.

So, we read the sensor via `digitalRead` many times (say, 20), and if all results are `LOW`, we (correctly) assume it is a true `LOW`, otherwise, it's not.

Maybe it's better to use `analogRead` provided by arduino, the problem is we are using `RAMP1.4`, which expose additional 6 digital stop pins by default, if we do not break it (to let the analog free by bend the pins), it's a replaceable and acceptable solution. Until other problems show up, we will stick to this workaround.

Oh, and don't forget we are using `INPUT_PULLUP` for our range pins (`HIGH` means still safe to move, so is default value).

``` cpp
pinMode(outRangePinPositive, INPUT_PULLUP);
pinMode(outRangePinNegative, INPUT_PULLUP);
```

# Update

20170515, the limit stop function OK!
20170419, We made it a library!
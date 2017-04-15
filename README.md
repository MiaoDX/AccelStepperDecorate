Some tips to use [`AccelStepper`](http://www.airspayce.com/mikem/arduino/AccelStepper):

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

### Disable pins to save energy and avoid stepper too hot

``` cpp
  stepper.moveTo(800);
  stepper.runToPosition();
  stepper.disableOutputs();
```

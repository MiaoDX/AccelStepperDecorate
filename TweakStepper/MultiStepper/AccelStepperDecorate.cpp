#include "AccelStepperDecorate.h"

AccelStepperDecorate::AccelStepperDecorate(char motorName,
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

                                           double disPerRound)
{

    /*参数赋值*/
    this->motorName = motorName;

    this->enablePin = enablePin;


    this->outRangePinNegative = outRangePinNegative;
    this->outRangePinPositive = outRangePinPositive;
    this->outRangeSwitch = outRangeSwitch;

    this->subdivision = subdivision;
    this->reductionRatio = reductionRatio;

    this->stepAngle = stepAngle;
    this->maxSpeed = maxSpeed;
    this->acceleration = acceleration;
    this->maxMovingDistance = maxMovingDistance;

    this->stepPerRound = 360.0 / this->stepAngle * this->reductionRatio * this->subdivision; //每圈脉冲数
    this->disPerRound = disPerRound;

    this->stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);

    this->setup();
}

AccelStepperDecorate::~AccelStepperDecorate()
{
    this->stepper.disableOutputs(); // release all pins
    //delete this->stepper;           // release stepper, HOW TO DO THIS?
}

void AccelStepperDecorate::setup()
{

    this->stepper.setPinsInverted(false, false, true); // this is hardcoded, may need some refine.
    this->stepper.setEnablePin(enablePin);

    this->stepper.setMaxSpeed(maxSpeed);
    this->stepper.setAcceleration(acceleration);

    pinMode(outRangePinPositive, INPUT);
    pinMode(outRangePinNegative, INPUT);
    // PULL UP?


    
}

int AccelStepperDecorate::dis2Pulses(double distance)
{
    return (int)((distance + 0.0) / this->disPerRound * this->stepPerRound); //	脉冲数 = 距离/每圈“距离”*每圈脉冲数
};

bool AccelStepperDecorate::run()
{
    if (!this->outRangeSwitch)
    { // no out-range
        this->stepper.run();
    }
    else
    {

        if (abs(this->stepper.distanceToGo()) % 100 == 0)
        { // every x stepper read once, hard code
            int outRangePin = (this->stepper.speed() > 0.0) ? outRangePinPositive : outRangePinNegative;
            if (digitalRead(outRangePin) == LOW)
            {                 //限位传感器平时为高电平，到限位区域返回低电平
                this->stop(); // this is not regular stop
                return false;
            }
        }

    } //else

    return true;
}

void AccelStepperDecorate::stop()
{
    this->stepper.disableOutputs(); // release all pins
}

/*
int stepMotor::motorToHome() {
	if (!this->outRangeSwitch) //不进行限位，说明是 y 轴，直接返回已知错误（y 轴没有归位操作）
		return knownRtn;

	if (this->_motorMove(INT_MAX, maxOutRangePulse) != knownRtn) { //先正向运动到边缘
		cout << "Unkown error when move motor to home!" << endl;
		return errorRtn;
	}

	return this->motorMove(-this->maxMovingDistance/2.0);
	//return this->_motorMove(-this->maxMovingDistance, maxOutRangePulse * 2);	//需要注意，是反向移动，且未防止出现限位可能的问题（即
	//移动到边缘后，在反向移动时限位信号还是存在的，可能会使平移台在正好在移出限位位置后停止的现象），将限位调大些
}
*/
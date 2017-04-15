/*
AccelStepperDecorate is a wrapper of `AccelStepper`, the aim is to not change a single line of original lib and just concentrate on what we need.

The functions we need is just:

dis2steps: change distance to steps, this depends on `disPerRound` which is the movement per round of stepper (can be distance or angel for different perpose)
run: run with possible caution of limit stop (out-of-range)
stop: use un-elegant stop, aka just disable all pins instead of run more steps as `AccelStepper` does
*/

#pragma once
#include <AccelStepper.h>
//#include <string>

class AccelStepperDecorate
{

  public:
    AccelStepperDecorate(char motorName,
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
                         double maxMovingDistance,  // NEEDS RECONSIDER!!!
                         
                         double disPerRound
                         );

    ~AccelStepperDecorate();


    void setup();
    
    int dis2Pulses(double distance);
    bool run();
    void stop();



    /*参数定义*/
  public:

    AccelStepper stepper;

    char motorName;
    /*pin connection*/


    /*since already have stepper and we won't use this pins anymore, just make them invisable*/
    /* 
    int dirPin,              //控制方向管脚
        stepPin,             //输出脉冲管脚
    */
    int enablePin;
   

    int outRangePinNegative, //限位信号1
        outRangePinPositive, //限位信号2

        /*configurable parameter*/
        subdivision,             //细分数
        reductionRatio = 1;      //减速比
    
    bool outRangeSwitch = true;

    /*static speed parameter*/
    double stepAngle = 1.8, //步距角
        maxSpeed = 300,
           acceleration = 50.0,
           maxMovingDistance = 0.0; //最大行程

    double disPerRound = 0.0; // 电机每圈对应的距离（这个距离可以是直线距离，也可以是角度值！！）


    /*calculate speed parameter*/
    double stepPerRound;                //每圈的脉冲数
};

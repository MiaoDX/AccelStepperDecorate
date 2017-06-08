/**
  PUT all pins specification in one file to make things easier
*/
#ifndef PinsAndConfiguration_h
#define PinsAndConfiguration_h


// For RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24


// platform specific
/*设备信息：
第一代平台：z 轴，正向 3，负向 2，每圈 1mm, 行程 38.5 mm
		   x 轴，正向 22，负向 21，每圈 5mm, 行程 58.5 mm
		   
第二代平台：z 轴，正向 3，负向 2，每圈 2mm, 行程 50.0 mm
		   x 轴，正向 22，负向 21，每圈 2mm, 行程 90.0 mm
		   
第三代平台：z 轴，正向 3，负向 2，每圈 2mm, 行程 75.0 mm
		   x 轴，正向 22，负向 21，每圈 2mm, 行程 150.0 mm		   

*/
#define X_MAX_MovingDistance	58.5
#define X_disPerRound			5
#define Z_MAX_MovingDistance	38.5
#define Z_disPerRound			1
#define YAW_MAX_MovingDistance	90
#define YAW_anglePerRound		5




#endif

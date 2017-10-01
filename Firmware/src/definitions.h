#include <Arduino.h>

#define MCP4921_CS 10
#define ENC_A A1
#define ENC_B A3
#define ENC_BTN A2
#define BTN_PWR 1
#define FAN 9
#define TEMP_SENS A0

#define ENC_STEPS_PER_NOTCH 4

//software defined limits
#define T_MAX 90   // 90°C
#define I_MAX 6000 // 6A
#define U_MAX 4000 // 40V

#define FAN_TEMP_HIGH 30 //temperature at which the an switches on
#define FAN_TEMP_LOW 27 //temperature at which the an switches off again

//from MCP9701 datasheet
#define Tc 19.5f
#define V0 400

#define USEC_PER_HOUR 1000L * 60L * 60L

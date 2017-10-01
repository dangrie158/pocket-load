#include <Arduino.h>

#define MCP4921_CS 10
#define ENC_A A1
#define ENC_B A3
#define ENC_BTN A2

#define ENC_STEPS_PER_NOTCH 4

#define T_MAX 90   // 90°C
#define I_MAX 6000 // 6A
#define U_MAX 4000 // 40V

#define USEC_PER_HOUR 1000L * 60L * 60L

#ifndef PICONTROLLER
#define PICONTROLLER

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

typedef struct {
    float Ki;
    float Kp;
    float Kd;
    float timestep;
    float errorSum;
    float prevError;
} controller;

extern controller PIController;
extern volatile uint8_t flag;

void initController(void);
float computeGain(controller *con, float measurement, float refAngle);

#endif
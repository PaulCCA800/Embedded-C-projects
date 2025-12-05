#ifndef SERVOUTILS
#define SERVOUTILS
#define F_CPU 12800000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

typedef enum {
    RISING,
    FALLING
} edge;

volatile edge edgeState; 
volatile uint8_t overFlow;
volatile uint16_t lastCapture; //16 bit for timer/counter unit 1. 
volatile uint16_t risingStamp;
volatile uint16_t highState;

void Timer1_init(void);
void initVars(void);
void setServoSpeed(int16_t servospeed);
float getServoAngle(void);
void setServoMidPos(void);

#endif


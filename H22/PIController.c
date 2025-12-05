#include "PIController.h"

controller PIController;
volatile uint8_t flag = 0;

void initController(void){
    PIController.Kp = 1;
    PIController.Ki = 0.5;
    PIController.Kd = 0;
    PIController.errorSum = 0;
    PIController.prevError = 0;
    PIController.timestep = 0.02;
};

float computeGain(controller *con, float measurement, float refAngle){
    float error = refAngle - measurement;
    con->errorSum += error * con->timestep;
    float gain = con->Kp * error + (con->Ki * con->errorSum) + (con->Kd * (error - con->prevError))/con->timestep;
    con->prevError = error;
    return gain;
};


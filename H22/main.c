#include "servoUtils.h"
#include "PIController.h"

int main(){
    Timer1_init();
    initVars();
    initController();
    while(1){
        if(flag == 1){
            flag = 0;
            setServoSpeed(computeGain(&PIController, getServoAngle(), ref_angle));
        }
    }

};
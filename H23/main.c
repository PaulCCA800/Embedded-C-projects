#include "displayUtil.h"
#include "displayDriver.h"

int main(void){
    initInput();
    displayInit();
    initTimer1();
    initInput();
    sensInit();
    initAComp();
    flow_rate = 0;
    water_consumed = 0;
    count = 0;
    lastCount = 0;
    sample = 0;
    lastSample = 0;
    while(1){
        if(flag == 1){
            flag = 0;
            flow_rate = lastCount/6.6;
            water_consumed += flow_rate/60;
            temp = lastSample * 0.0625 - 50;
            updateDisplay();
        }
    }
}
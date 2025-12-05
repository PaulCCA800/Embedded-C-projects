#include "servoUtils.h"
#include "PIController.h"

void Timer1_init(void){
    //Data Direction registers and pull up enable on pin PE0. 
    DDRE &= ~(1 << PE0);
    PORTE |= (1 << PE0);
    DDRE |= (1 << PE2);

    cli();

    //Fast PWM, configure unit 1 to mode 15.
    TCCR1A &= 0;
    TCCR1A |= (1 << WGM11) | (1 << WGM10) | (1 << COM1B1);
    TCCR1A &= ~(1 << COM1B0);

    TCCR1B &= 0;
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    TCCR1B |= (1 << ICES1) | (1 << ICNC1);

    //Clear potential flags and enamble interrupts. 
    TIFR |= (1 << TOV1) | (1 << ICF1);
    TIMSK |= (1 << TOIE1) | (1 << TICIE1);

    OCR1A = 31999;
    OCR1B = 2399;

    sei();
}

void initVars(void){
    edgeState = RISING;
    overFlow = 0;
    lastCapture = 0;
    risingStamp = 0;
    highState = 0;
};

void setServoSpeed(int16_t servospeed){
    if(servospeed >= 352){
        OCR1B = 2047;
    }
    else if(servospeed <= -352){
        OCR1B = 2751;
    }
    else{
        OCR1B = (2399 - servospeed);
    }
};

float getServoAngle(void){
    duty = 100 * (float)highState/(float)OCR1A;
    return 360 * (duty - 2.9)/(95.2);
};

void setServoMidPos(void){
    angle = getServoAngle();
    if(angle < 180){
        setServoSpeed(50);
    }
    else if(angle > 180){
        setServoSpeed(-50);
    }
    else{
        setServoSpeed(0);
    }
};

ISR(TIMER1_CAPT_vect){
    lastCapture = ICR1;
    if(edgeState == RISING) {
        edgeState = FALLING;
        risingStamp = lastCapture;
        TCCR1B &= ~(1 << ICES1);
        lastCapture = 0;
    }
    else{
        edgeState = RISING;
        TCCR1B |= (1 << ICES1);
        highState = lastCapture - risingStamp + overFlow * OCR1A;

    }
};

ISR(TIMER1_OVF_vect){
    overFlow += 1;
    flag = 1;
}
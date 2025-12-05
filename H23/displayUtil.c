#include "displayUtil.h"

volatile uint8_t flag = 0;
volatile uint8_t flagCapt = 0;

volatile float flow_rate;
volatile float water_consumed;
volatile float temp;
volatile float count;
volatile float lastCount;
volatile float sample;
volatile float lastSample;

void initInput(void){
    DDRE &= ~(1 << DDE0);
    PORTE |= (1 << PE0);
}

void sensInit(void){
    DDRA |= (1 << DDA0);
    PORTA &= ~(1 << PA0);
}

void sensOn(void){
    ACSR |= (1 << ACI);
    ACSR |= (1 << ACIE);
    PORTA |= (1 << PA0);
}

void sensOff(void){
    ACSR &= ~(1 << ACIE);
    PORTA &= ~(1 << PA0);
}

void initAComp(void){
    cli();

    DDRB &= ~(1 << DDB3);
    ACSR |= (1 << ACIS1) | (1 << ACIS0) | (1 << ACBG);
    
    sei();
 }

void initTimer1(void){

    cli();

    TCCR1A = 0;
    TCCR1B = (1 << CS11) | (1 << CS10) | (1 << ICNC1) | (1 << ICES1); 
    TIMSK = (1 << TOIE1) | (1 << TICIE1) | (1 << OCIE1A);

    TIFR = (1 << TOV1) | (1 << ICF1) | (1 << OCF1A);

    OCR1A = 6760;
    sei();
}

ISR(TIMER1_OVF_vect){
    lastCount = count;
    count = 0;
    sensOn();
    flag = 1;
}

ISR(TIMER1_CAPT_vect){
    count += 1;
}

ISR(ANALOG_COMP_vect){
    sample += 1;
}

ISR(TIMER1_COMPA_vect){
    lastSample = sample;
    sample = 0;
    sensOff();
}
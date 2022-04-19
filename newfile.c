#include <stdio.h>
#include <stdlib.h>
#include <xc.h> //XC compiler header
#pragma config WDTE = OFF 
#pragma config MCLRE = OFF          //sets RE3 to digital input
#pragma config LVP = OFF
#define _XTAL_FREQ 8000000 //Crystal Oscillator Frequency

//ADIF interupt bit when ADC convsersion is done. needs to be cleared in software
//RA0/AN0/C12IN0-


void main(void){
ADCON1= 0b00000000;
ANSEL = 0b00000001;
TRISA = 0b11111111;
PIR1 = 0b00000000;
PIR1bits.ADIF = 0;        //interrupt flag must be cleared by software
PIE1bits.ADIE = 1;          //enables ADC interrupt
ADCON0 = 0b10000001;    //GO is bit 1, enable is bit 0
ADCON0bits.CHS=0b0010;
TRISB = 0; // Set RB0 to output('0')
PORTB = 0; //Set PORTB pins to logic ?0?
int temp;
__delay_ms(10);
while(1){
    ADCON0bits.GO=1;            //starts the ADC conversion, automatically resets to 0 once it is done.
    __delay_ms(10);  
    //small, un-noticeable delay just so that GO register isn't read before the conversion is done
    while(1){
    if(ADCON0bits.GO==0){
        //temp = (ADRESH * 20 / 1024 - 1.6462)/(1-.9872);
        break;
    }
  
}
return temp;
}

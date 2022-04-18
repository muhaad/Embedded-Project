
#include <stdio.h>
#include <stdlib.h>
#include <xc.h> //XC compiler header

#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config LVP = OFF    //allows DS4 to be used
#define _XTAL_FREQ   8000000



#define LCD_E        RC7   // Enable pin for LCD
#define LCD_RS       RC5   // RS pin for LCD
#define LCD_Data_Bus   PORTB // Data bus for LCD
// Define Pins direction register
#define LCD_E_Dir         TRISA7
#define LCD_RS_Dir        TRISA5
#define LCD_Data_Bus_Dir   TRISB


void Water_Lvl(void){    
    ADCON1= 0b00000000;
    ANSEL = 0b00000001;
    TRISA = 0b11111111;
    PIR1 = 0b00000000;
    PIR1bits.ADIF = 0;        //interrupt flag must be cleared by software
    PIE1bits.ADIE = 1;          //enables ADC interrupt
    ADCON0 = 0b10000001;    //GO is bit 1, enable is bit 0
    ADCON0bits.CHS=0b0010; //AN2
    TRISB = 0; // Set RB0 to output('0')
    PORTB = 0; //Set PORTB pins to logic ?0?
    __delay_ms(10);
    ADCON0bits.GO=1;            //starts the ADC conversion, automatically resets to 0 once it is done.
    __delay_ms(10); //small, un-noticeable delay just so that GO register isn't read before the conversion is done
    
    while(1){
        if(ADCON0bits.GO==0){
            if(ADRESH<80){
                PORTB = 0b00000100; //Stop pouring water here, healthy water level.
           
                WriteCommandToLCD(0x3C);
                WriteCommandToLCD(0x0C1);
                char msg[] = "Refill Water";
                WriteStringToLCD(msg);  
                break;
            }
            else{  
                WriteCommandToLCD(0x3C);
                WriteCommandToLCD(0x0C1);
                char msg[] = "Water lvl OK";
                WriteStringToLCD(msg); 
                break;
            }
        }
    }
    return;
}

void Moisture_Lvl(void){    
    
    double moistureLvl;
    
    ADCON1= 0b00000000;
    ANSEL = 0b00000001;
    TRISA = 0b11111111;
    PIR1 = 0b00000000;
    PIR1bits.ADIF = 0;        //interrupt flag must be cleared by software
    PIE1bits.ADIE = 1;          //enables ADC interrupt
    ADCON0 = 0b10000001;    //GO is bit 1, enable is bit 0
    ADCON0bits.CHS=0b0001; //AN1
    TRISB = 0; // Set RB0 to output('0')
    PORTB = 0; //Set PORTB pins to logic ?0?
    __delay_ms(10);
    ADCON0bits.GO=1;            //starts the ADC conversion, automatically resets to 0 once it is done.
    __delay_ms(10); //small, un-noticeable delay just so that GO register isn't read before the conversion is done
    
    while(1){
        if(ADCON0bits.GO==0){
            if(ADRESH<614){
                moistureLvl = ((ADRESH % 614) /614)* 100; // moistureLvl value between 0.0-100.0
           
                WriteCommandToLCD(0x3C);
                WriteCommandToLCD(0x0C1);
                char msg[] = "Moisture ";
                WriteStringToLCD(msg);  
                break;
            }
            else{  
                break;
            }
        }
    }
    return;
}

void WriteCommandToLCD(unsigned char);
void WriteDataToLCD(char);
void InitLCD(void);
void WriteStringToLCD(const char*);
void ClearLCDScreen(void);
//Program start from here

void ToggleEpinOfLCD(void)
{
    PORTCbits.RC7 = 1;                // Give a pulse on E pin
    __delay_us(500);      // so that LCD can latch the
    PORTCbits.RC7 = 0;                // data from data bus
    __delay_us(500);
}
void WriteCommandToLCD(unsigned char Command)
{
    PORTCbits.RC5 = 0;               // It is a command
    PORTB = Command;   // Write Command value on data bus
    ToggleEpinOfLCD();
}
void WriteDataToLCD(char LCDChar)
{
    PORTCbits.RC5 = 1;               // It is data
    if(LCDChar=='°'){
        PORTB=0b11011111;
    }
    else{
    PORTB = LCDChar;   // Write Data value on data bus
    }
    
    ToggleEpinOfLCD();
}
void InitLCD(void)
{
    // Firstly make all pins output
    LCD_E          = 0;      // E = 0
    LCD_RS           = 0;      // D = 0
    LCD_Data_Bus     = 0;      // CLK = 0
    LCD_E_Dir        = 0;      // Make Output
    LCD_RS_Dir       = 0;      // Make Output
    LCD_Data_Bus_Dir = 0;      // Make Output
    WriteCommandToLCD(0x38);    //function set
    WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
    WriteCommandToLCD(0x01);    //clear display
    WriteCommandToLCD(0x06);    //entry mode, set increment
    
   
}
void WriteStringToLCD(const char *s)
{
    while(*s)
    {
        WriteDataToLCD(*s++);   // print first character on LCD
    }
}
void ClearLCDScreen(void)
{
    WriteCommandToLCD(0x01);    // Clear the screen
    __delay_ms(2);              // Delay for cursor to return at zero position
}

int main(void)
{
   ANSEL=0;
   TRISC=0;
   TRISAbits.TRISA0=1;
   ANS0=1;
   
   TRISB = 0; // Set RB0 to output('0')
   InitLCD();                // Initialize LCD in 8bit mode
//    char msg[] = "Temperature:10°C";
//    
//    ClearLCDScreen();          // Clear LCD screen
//    WriteStringToLCD(msg);  
//    WriteCommandToLCD(0x3C);
//    WriteCommandToLCD(0x0C1);
//    char msag[] = "Humidity:25%";
//    WriteStringToLCD(msag);  
    
	while(1){
    }
   
    return 0;
}




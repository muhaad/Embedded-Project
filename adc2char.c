#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void WriteDataToLCD(char LCDChar){
    printf("%c\n",LCDChar);   
   // ToggleEpinOfLCD();
}
void WriteStringToLCD(const char *s){
    while(*s)
    {
      WriteDataToLCD(*s++);  
    }
}
int main() {
    char buffer[2];
    unsigned char num = 0b00001111;
    char msg[] = "Temperature:";
    printf("Hello, world!\n");
   // WriteCommandToLCD 80 first line C0 second line
    
    sprintf(buffer,"%d",num); //converts adc val to char
    strcat(msg,buffer); // concatenate buffer to end of msg
    strcat(msg,"°C");
    WriteStringToLCD(msg);
    printf("Humidity: %s\n",buffer);
    return 0;
}
  

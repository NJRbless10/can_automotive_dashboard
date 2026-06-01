
#include "ECU2_Sensor.h"
#include "ADC.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

#define _XTAL_FREQ 8000000

int rpm;
char ssd[4];  
char status;


void display(char *data)
{
    for( int i = 0 ; i < 4 ; i++ )
    {
        PORTD = data[i];   // Send segment data
        PORTA = (unsigned char)((PORTA & 0XF0) | (1 << i)); // Select digit
        for( int delay_1 = 10000; delay_1--; ); // Multiplexing delay
    }
}

uint16_t get_rpm()
{
    //Implement the rpm function
    rpm = ((unsigned long)read_adc(CHANNEL4) * 6000) / 1023;
    
    // Convert count to 4-digit display
    ssd[0] = ((rpm / 1000) % 10) + '0';
    ssd[1] = ((rpm / 100) % 10) + '0';
    ssd[2] = ((rpm / 10) % 10) + '0';
    ssd[3] = (rpm % 10) + '0';
    
    can_transmit(RPM_MSG_ID ,ssd ,4);
    __delay_ms(20);  
    
    return rpm;
}


IndicatorStatus process_indicator()
{
    unsigned key = read_digital_keypad(STATE_CHANGE);

    if(key == 0x0e)
    {
        status = 1;      
    }
    else if(key == 0x0b)
    {      
        status = 2;     
    }
    else if(key == 0x0d)
    {
       
        status = 0;
        
    }
    
    
    can_transmit(INDICATOR_MSG_ID ,&status,1);  
    __delay_ms(20);
      
}
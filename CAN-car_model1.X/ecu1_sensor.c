#include "ecu1sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "digital_keypad.h"
#include "uart.h"
#include "clcd.h"
char gear[9][3]={"ON","GN","G1","G2","G3","G4","G5","Rr","Cl"};
int ind = 0;
#define _XTAL_FREQ 8000000

uint16_t msg_id;
uint8_t rx1_data[4];
char len1;

uint16_t gear_id;
uint8_t rx2_data[4];
char len2;

uint16_t get_speed()
{
    char str[3];
   unsigned short speed= read_adc(CHANNEL4)/10.33;
   str[0]=(speed/10)+48;
   str[1]=(speed%10)+48;
   str[2]='\0';
    
   
   can_transmit(SPEED_MSG_ID ,str,2);
   __delay_ms(20);
   
  /* 
   __delay_ms(20);
   can_receive(&msg_id,rx1_data,&len1);
   rx1_data[len1] = '\0';
       
    if(msg_id == SPEED_MSG_ID)
    {
       clcd_print("SPEED", LINE1(0));
       clcd_print(rx1_data, LINE2(0));
    }
   */
   return speed;
}

unsigned char get_gear_pos()
{
    
    // Implement the gear function
    
    int key=read_switches(STATE_CHANGE);
    if(key== 1)
    {
        if(ind<7)
        {
            ind++;
        }
    }
    else if(key == 2)
    {
        if(ind>0)
        {
            ind--;
        }
    }
    else if(key== 3)
    {
        ind=8;
    }
    
   can_transmit(GEAR_MSG_ID ,gear[ind],2);
    __delay_ms(20);
   
  /* For LOOP Back method
    __delay_ms(20);
   can_receive(&gear_id,rx2_data,&len2);
   
    //clcd_print("GEAR", LINE1(9));
   
   rx2_data[len2] = '\0';
   if(gear_id == GEAR_MSG_ID)s
   {
       clcd_print("GEAR", LINE1(9));
       clcd_putch(rx2_data[0], LINE2(9));
       clcd_putch(rx2_data[1], LINE2(10));
   }
    */
    
    return gear[ind][0];
    
}
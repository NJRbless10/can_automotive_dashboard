
#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

void init_ssd()
{
    TRISD = 0x00;          // Segment lines
    TRISA = TRISA & 0xF0;  // Digit select lines
    PORTA = PORTA & 0xF0;
}


void init_config()
{
    init_adc();
    init_digital_keypad();
    init_can();
}

int main()
{
    init_config();
    
    //call the functions
    while(1)
    {
        get_rpm();
        process_indicator();
    }
}
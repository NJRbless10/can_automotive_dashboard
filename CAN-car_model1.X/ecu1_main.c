#include "adc.h"
#include "can.h"
#include "ecu1sensor.h"
#include "msg_id.h"
#include "uart.h"
#include "clcd.h"
#include "digital_keypad.h"

int main()
{
    //init_clcd();
    init_adc();
    init_matrix_keypad();
    init_can();
    
    
    while(1)
    {
        get_speed();
        get_gear_pos();
    }
}
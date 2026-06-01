/*File for CAN configuration , setting message id's, Data Transmission, */
#include <xc.h>
#include "can.h"
#include "clcd.h"

/* CAN operation mode values*/
typedef enum _CanOpMode {
    /* Use this to access opcode bits */
    e_can_op_mode_normal = 0x00,
    e_can_op_mode_loop = 0x40,
    e_can_op_mode_config = 0x80
} CanOpMode;

/*Configuration function for CAN */
void init_can(void) {
    /* CAN_TX = RB2, CAN_RX = RB3 */
    TRISB2 = 0; /* CAN TX */
    TRISB3 = 1; /* CAN RX */

    /* Enter CAN module into configuration mode */
    /* clear previous mode */
    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_config); /* set new mode */

    /* Wait until desired mode is set */
    while (CANSTAT != 0x80);

    /* Enter CAN module into Mode 0 */
    ECANCON = 0x00;

    /* Initialize CAN Timing 8MHz */
    BRGCON1 = 0xE1; /* 1110 0001, SJW=4, TQ, BRP 4 */
    BRGCON2 = 0x1B; /* 0001 1011, SEG2PHTS 1 sampled once PS1=4TQ PropagationT 4TQ */
    BRGCON3 = 0x03; /* 0000 0011, PS2, 4TQ */

    /*
     * Enable Filters
     * Filter 0
     */
    RXFCON0 = 0x00;
    /* Enter CAN module into Loop back mode */
    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal);

    /* Set Receive Mode for buffers */
    RXB0CON = 0x00;
    RXB0CONbits.RXM0 = 1;
    RXB0CONbits.RXM1 = 1;
}

static uint16_t get_msg_id_std(void) {
    uint16_t id = 0;
    id = ((RXB0SIDL >> 5) & 0x7) | (RXB0SIDH << 3);
    return id;
}

/*function for the setting the message id's*/
static void set_msg_id_std(unsigned int id) {// set 8bit to 11bits
    TXB0SIDL = (id & 0x7) << 5;
    TXB0SIDH = (id >> 3);
}

/*DATA transmission function for Speed and Gear change*/

void can_transmit(uint16_t msg_id, const uint8_t *data, uint8_t len) 
{
    uint8_t *ptr;
    TXB0EIDH = 0x00; /* Extended Identifier */
    TXB0EIDL = 0x00; /* Extended Identifier */

    // Set MSG ID
    set_msg_id_std(msg_id); // set 8bit to 11bits

    // Set data length
    TXB0DLC = len;//if we send only 2bytes so send the size as 2bytes
    /* Send the data by writing the bytes to individual 
     *  TXB0D0, TXB0D1 .... TXB0D7
     * Max length should be 8 (No error handing here :(
     * */
    ptr = (uint8_t *) & TXB0D0;
    for (int i = 0; i < len; i++) {//transmitting the data if we send 2bytes until length time
        ptr[i] = data[i];       //eg; if 2bytes ptr[0] = data[0] , ptr[1] = data[1];
        
    }
    TXB0REQ = 1; /* Set the buffer to transmit */
}

/* Function to receive CAN bus data
 * len can be zero if no data is available
 * Mandatory for caller to check len before processing
 * */
void can_receive(uint16_t *msg_id, uint8_t *data, uint8_t *len) {//all the parameters are empty because we will receive the data from tx
    uint8_t *ptr;

    if (RXB0FUL) /* CheckRXB0 */ {
        // Get MSG ID
        *msg_id = get_msg_id_std();
        // Get data length
        *len = RXB0DLC;

        ptr = (uint8_t *) & RXB0D0;
        // Read data
        for (int i = 0; i < *len; i++) {
            data[i] = ptr[i];
        }

        RXB0FUL = 0; // Clear buffer flag
        RXB0IF = 0; // Clear interrupt flag   
    }

    // No data available.
    //*len = 0;
}

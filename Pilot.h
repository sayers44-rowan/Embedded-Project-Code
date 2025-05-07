
#include "msp430fr2355.h"

#include <msp430.h>




// Initializes Solenoid on P5.4
 void initSolenoid(void)
{
    P5DIR |= BIT4;     // Set P5.4 as output
    P5OUT &= ~BIT4;    // Solenoid OFF initially
}

// Turn Solenoid ON and light up Red LED
 void solenoidON(void)
{
    P5OUT |= BIT4;     // Set P5.4 HIGH
          // Turn on Red LED (P5.0)
}

// Turn Solenoid OFF and turn off Red LED
 void solenoidOff(void)
{
    P5OUT &= ~BIT4;    // Set P5.4 LOW
           // Turn off Red LED
}




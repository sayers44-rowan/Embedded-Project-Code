
#include "msp430fr2355.h"
#include <msp430.h>

// Initializes P5.0 as output for Red LED
 void initRedLED(void)
{
    P5DIR |= BIT0;    // Set P5.0 as output
    P5OUT &= ~BIT0;   // Turn off LED initially
}

// Turns the Red LED on
 void redLEDOn(void)
{
    P5OUT |= BIT0;
}

// Turns the Red LED off
void redLEDOff(void)
{
    P5OUT &= ~BIT0;
}

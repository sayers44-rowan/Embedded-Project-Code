#include <msp430fr2355.h>
#include "RGBLEDFINAL.h"
#include "SERVOFINAL.h"


enum system_state {IDLE, HEATING} state;


void initADC(void);
unsigned int readADC(void);


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer


    // Configure LEDs
    P1OUT &= ~BIT0;
    P1DIR |= BIT0;
    P6OUT &= ~BIT6;
    P6DIR |= BIT6;


    // Unlock GPIO
    PM5CTL0 &= ~LOCKLPM5;


    // Initialize RGB
    initRGB();


    // Initialize ADC
    initADC();


    state = IDLE;


    while (1)
    {
        unsigned int adcValue = readADC();


        // Choose threshold for switching states
        if (adcValue > 512)
            state = HEATING;
        else
            state = IDLE;


        switch (state)
        {
            case IDLE:
                setRGBLED(0, 255, 0);  // Green
                ServoClose();
                break;
            case HEATING:
                setRGBLED(0, 0, 255);  // RED
                ServoOpen();
                break;
        }


        __delay_cycles(50000); // Delay for stability
    }
}


void initADC(void)
{
    // Configure ADC input pin (P1.5 = A5)
    P1SEL0 |= BIT5;
    P1SEL1 |= BIT5;


    ADCCTL0 &= ~ADCENC;                     // Disable ADC before configuration
    ADCCTL0 = ADCSHT_2 | ADCON;             // Sample-and-hold time, ADC on
    ADCCTL1 = ADCSHP;                       // ADC sample-and-hold pulse-mode
    ADCCTL2 = ADCRES;                       // 10-bit resolution (0-1023)
    ADCMCTL0 = ADCINCH_5;                   // A5 input channel
    ADCCTL0 |= ADCENC;                      // Enable ADC
}




unsigned int readADC(void)
{
    ADCCTL0 |= ADCENC | ADCSC;              // Start sampling/conversion
    while (ADCCTL1 & ADCBUSY);              // Wait for completion
    return ADCMEM0;                         // Return ADC value
}

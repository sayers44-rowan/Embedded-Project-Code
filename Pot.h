#include <msp430fr2355.h>
#include <msp430.h>

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
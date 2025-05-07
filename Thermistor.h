#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include <msp430.h>

// Configures the ADC to read from the thermistor on P1.6 (A6)
static inline void configureThermistorADC(void)
{
    // Select P1.6 as ADC input (A6)
    P1SEL0 |= BIT6;
    P1SEL1 |= BIT6;

    ADCCTL0 &= ~ADCENC;                        // Disable ADC to configure
    ADCCTL0 = ADCSHT_2 | ADCON;                // ADC ON, sample-and-hold time
    ADCCTL1 = ADCSHP | ADCSSEL_2;              // Use sampling timer, SMCLK
    ADCCTL2 = ADCRES_2;                        // 12-bit resolution
    ADCMCTL0 = ADCINCH_6;                      // Input channel A6 (P1.6)
}

// Reads the ADC value from the thermistor (returns 0–4095)
static inline unsigned int readThermistorADC(void)
{
    ADCCTL0 |= ADCENC | ADCSC;                 // Enable and start conversion
    
    // Wait for the conversion to complete by checking the BUSY flag
    while (ADCCTL1 & ADCBUSY) {
        // Optionally add a timeout here if needed
    unsigned int timeout = 5000;  // Set timeout count (adjust as needed)
while (ADCCTL1 & ADCBUSY && timeout > 0) {
    timeout--;
    if (timeout == 0) {
        // Timeout condition: handle as needed (e.g., return an error)
        return 0;  // or other error value
    }
}
    }

    // Clear the ADCBUSY flag after conversion is complete
    ADCCTL1 &= ~ADCBUSY;                       // Clear the busy flag (optional, but good practice)

    return ADCMEM0;                            // Return result
}

#endif /* THERMISTOR_H_ */
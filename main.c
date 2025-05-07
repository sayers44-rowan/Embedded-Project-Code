#include <msp430fr2355.h>
#include "RGBLEDFINAL.h"
#include "SERVOFINAL.h"
#include "Thermistor.h"
#include "Pot.h" 
#include "REDLED.h"
#include "Pilot.h"
#include "intrinsics.h"

enum system_state {SET_TEMP, IDLE, HEATING} state;


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // Unlock GPIO
    PM5CTL0 &= ~LOCKLPM5;

    // Configure onboard LEDs
    P1OUT &= ~BIT0;
    P1DIR |= BIT0;
    P6OUT &= ~BIT6;
    P6DIR |= BIT6;

    // Initialize peripherals
    

    state = SET_TEMP;   // Start in temperature setting state

    while (1)
    {
        initSolenoid();
        initRGB();
        initRedLED();

        unsigned int tempValue = readThermistorADC(); // Thermistor ADC value
        
        switch (state)
        {
            case SET_TEMP:
                setRGBLED(255, 0, 0); // Blue - waiting for warm-up
                __delay_cycles(4000000);
                ServoClose();
                solenoidOff();
                redLEDOff();
                

                // Wait until temperature rises above a set threshold
                if (tempValue < 150 )  // Adjust threshold as needed
                {
                    state = IDLE;

                }
                break;

            case IDLE:
                solenoidOff();
                setRGBLED(0, 255, 0);  // Green
                ServoClose(); 
                redLEDOff();
                break;

            case HEATING:
                solenoidON(); 
                setRGBLED(0, 0, 255);  // red
                ServoOpen(); 
                redLEDOn();
                break;
        }

        // Potentiometer controls state after boiler is hot enough
        if (state != SET_TEMP)
        {
           initADC();
            unsigned int potValue = readADC(); // Read potentiometer
            if (potValue > 512)
                state = HEATING;
               
            else
                state = IDLE;   
                
                
        }

        __delay_cycles(50000); // Delay for stability
    }
}
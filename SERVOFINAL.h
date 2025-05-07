#include "msp430fr2355.h"
#include <msp430.h>

void ServoOpen() {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // Set up PWM output on P2.1
    P2DIR |= BIT1;
    P2SEL0 |= BIT1;
    P2SEL1 &= ~BIT1;

    PM5CTL0 &= ~LOCKLPM5;

    // Configure Timer B1 for PWM
    TB1CCR0 = 20000;               // PWM period (20 ms for servo)
    TB1CCTL2 = OUTMOD_7;           // Reset/set mode
    TB1CTL = TBSSEL_2 | MC__UP;    // SMCLK, up mode

    // Move to initial position
   // TB1CCR2 = 500;                 // ~0° position
  //  __delay_cycles(1500000);      // 1.5 sec delay

    // Move to final position
    TB1CCR2 = 1200;                // ~90° position (example)
    __delay_cycles(1500000);      // 1.5 sec delay

    // Keep PWM running at last position
    // Do not change TB1CCTL2 or TB1CTL — this holds the servo
}

void ServoClose() {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // Set up PWM output on P2.1
    P2DIR |= BIT1;
    P2SEL0 |= BIT1;
    P2SEL1 &= ~BIT1;

    PM5CTL0 &= ~LOCKLPM5;

    // Configure Timer B1 for PWM
    TB1CCR0 = 20000;               // PWM period (20 ms for servo)
    TB1CCTL2 = OUTMOD_7;           // Reset/set mode
    TB1CTL = TBSSEL_2 | MC__UP;    // SMCLK, up mode

    // Move to initial position
    TB1CCR2 = 500;                 // ~0° position
    __delay_cycles(1500000);      // 1.5 sec delay

    // Move to final position
   // TB1CCR2 = 1200;                // ~90° position (example)
  //  __delay_cycles(1500000);      // 1.5 sec delay

    // Keep PWM running at last position
    // Do not change TB1CCTL2 or TB1CTL — this holds the servo
}
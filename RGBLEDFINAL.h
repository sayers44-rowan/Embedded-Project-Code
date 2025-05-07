#include <msp430fr2355.h>
#include <msp430.h>

void initRGB(){
    P6DIR |= BIT0 | BIT1 | BIT2;                     // P6.0 - P6.2 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;  
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);                   // P6.0 - P6.2 select to
    
    

    TB3CCR0 = 1000-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_3;                      // CCR1 reset/set
    TB3CCR1 = 750;                            // CCR1 PWM duty cycle
    TB3CCTL2 = OUTMOD_3;                      // CCR2 reset/set
    TB3CCR2 = 250;                            // CCR2 PWM duty cycle
    TB3CCTL3 = OUTMOD_3;                      // CCR3 reset
    TB3CCR3 = 250;                            // CCR3 PWM DUTY
   
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;   //TBR

              
    
}
// set led rgb sets the rgb to a specific color
void setRGBLED(char Red, char Green, char Blue ) {
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2; 
    TB3CCR1 = Blue << 2; 
}


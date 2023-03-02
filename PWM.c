/**
 * \file:   PWM.c
 * \author: anton
 *
 * \date 1 de Março de 2023, 15:46
 */

#include <xc.h>
#include <stdint.h>
#include "PWM.h"

void PWMconfigPR2(TypeBTimerPreScalers_t T2Prescaler, uint16_t T2PR2Val){
    /*
    OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL = 0;// Use timer T2 as the time base for PWM generation
    OC2CONbits.ON = 1;
    TypeBTimer16bitSetFreq( 2 , Freq);
    //Timer2Start();
    */
}    
   /**
 * \brief Configures Timer2 and OC2 module to generate a PWM signal.
 * 
 * Configures PWM module and Timer2 for generating a PWM signal with
 * duty-cycle defined by PWMsetDutyCycle() and a frequency Freq (in Hz). 
 * 
 * PWMconfigFreq() performs the required initialisations and turns 
 * OC2 module on. Timer2Start() must be called afterwards for starting Timer2. 
 * 
 * @param Freq      PWM Frequency
 */
void PWMconfigFreq(uint16_t Freq){
    OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL = 0;// Use timer T2 as the time base for PWM generation
    OC2CONbits.ON = 1;
    TypeBTimer16bitSetFreq( 2 , Freq);
    //Timer2Start();
}
    


/**
 * \brief Sets the duty-cycle of PWM output. 
 * 
 * @param DutyCycle     Duty-Cycle value (0 to 100)
 */
void PWMsetDutyCycle(uint8_t DutyCycle){
    OC2RS = ((PR2 + 1) * DutyCycle)/100 ;
}


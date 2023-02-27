/**! 
 * \file  mainProj0.c
 * \author Pedro Fonseca <pf@ua.pt>
 *
 * \date 26 January 2023, 17:18
 * 
 * \brief Demo program of Project 0 
 * 
 * \mainpage 
 * 
 * Example of a program for Project 0 of Electronic Instrumentation Systems. 
 * 
 * The code will read a voltage signal in AN0 pin at a sampling frequency 
 * SampFreq, deliver that value as the argument to the function 
 * transferFunction() and generate a PWM signal, where the duty-cycle is 
 * controller by the output of transferFunction() and the frequency is PWMfreq. 
 * Both SampFreq and PWMfreq are defined as constants in the main(). 
 * 
 * This example is distributed as a main file (in mainProj0.c) and the header
 * files of the modules used in the project: 
 * - timer.h
 * - analog.h
 * - PWM.h
 * - uart.h 
 * - pic32conf.h
 */

/* Configuration bits */

#include "../SIE_Proj0_demo.X/../common/config_bits.h"
//#include "../common/config_bits.h"
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

//#include "../common/UART/uart.h"
#include "../SIE_Proj0_demo.X/../common/UART/uart.h"
#include "pic32conf.h"
#include "timer.h" 
#include "analog.h"
#include "PWM.h"

/**
 * \brief Example of a transfer function. 
 * 
 * The example provided is a "dummy" transfer funtion, that only performs a 
 * scale change: converts an input voltage in the range [0V..2V] applied to a 
 * ADC in the range [0V..3.3V] to a value for 0 to 100. 
 * 
 * \param inVal     Value returned by the ADC
 * \return          Converted value in the range 0..100 for a input
 */
uint16_t tf_direct(uint16_t inVal);


/**
 * Average of n samples
 * 
 * n is defined as a const int in the function body. 
 * 
 * @param inVal     value read in the analog input (0 to 1023)
 * @return      average of the last n input values, scaled for a range 0..100.
 */
uint16_t tf_avgNSamples(uint16_t inVal);

int main(void) {
    int cont = 0;
    TypeBTimer16bitSetFreq(2, 10);
    // Set RA3 as output
    TRISAbits.TRISA3 = 0;
    //UartInit(PBC, 115200L);
    TMR2 = 0;
    PutChar('x');
    
    while(1){
        while(Timer2GetEOC() == 0);
        cont++;
        if(cont % 10 == 0){
            PORTAbits.RA3 = !PORTAbits.RA3;
        }
        
        Timer2ClearEOC();
    }
}


/**
 * Direct transfer function 
 * 
 * "Echoes" the input value to the output, adjusting the output range to 0..100
 * 
 * @param inVal     value read in the analog input (0 to 1023)
 * @return          input value, range adjusted to 0..100
 */
uint16_t tf_direct(uint16_t inVal)
{
    return inVal*100/1024; 
}


/**
 * Average of n samples
 * 
 * n is defined as a const int in the function body. 
 * 
 * @param inVal     value read in the analog input (0 to 1023)
 * @return      average of the last n input values, scaled for a range 0..100.
 */
uint16_t tf_avgNSamples(uint16_t inVal) {
    
#define nSamples 3 
    
    uint16_t val; 
    
    static uint16_t Samples[nSamples];
    static int pointer; 
    
    /*
     * Move pointer to next position 
     */
    pointer++;
    pointer=(pointer)%nSamples; 
    
    /* Update Samples array */
    Samples[pointer] = inVal*100/1024; 
    
    /* Compute the average */
    val = 0; 
    int i; 
    for(i=0; i< nSamples; i++){
        val += Samples[i];
    }
   
    return val/nSamples; 
}
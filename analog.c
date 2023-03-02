/**
 * \file:   analog.c
 * \author: anton
 *
 * \date 24 de Fevereiro de 2023, 17:35
 */

#include <xc.h>
#include <stdint.h>
#include "analog.h"


void ADCconfig(uint8_t SourceChannel, ADCTriggerSrc_t ConversionTriggerSource, uint8_t SampleTime){
    TRISB = TRISB | 0xFFFF; // 
    AD1PCFG = AD1PCFG & 0x0000; // all RB ports configured as analog input
    AD1CON1bits.CLRASAM = 1;
    // Selects AN4 as input for the A/D converter
    AD1CHSbits.CH0SA = SourceChannel;
    // Configuração do número de conversões consecutivas do mesmo canal
    AD1CON2bits.SMPI = 0; // xx + 1 samples will be converted and stored
    // in buffer locations ADC1BUF0 to ADC1BUFxx+1
    AD1CON3bits.SAMC = SampleTime; // Sample time is 16 TAD (TAD = 100 ns)
   
    AD1CON1bits.SSRC = ConversionTriggerSource;  // Stop conversions when the 1st A/D converter  interrupt is generated

    AD1CON1bits.FORM = 0; // Format is Integer 16-bit
    AD1CON2bits.VCFG = 0; // Voltage sources are AVdd and AVss
    AD1CON2bits.CSCNA = 0; // no scanning of multiple inputs
    AD1CON2bits.BUFM = 0; // Buffer fill mode: one 16-word buffer
    AD1CON2bits.ALTS = 0; // Always use MUX A
    AD1CON3bits.ADRC = 0; // ADC clock source is PB Clock
    AD1CON3bits.ADCS = 7; // ADC clock prescaler is set to 7

}    
   
/**
 * \brief Turns ADC module off
 */
void ADCoff(void){
    AD1CON1bits.ON = 0; // Disable A/D converter
}

/**
 * \brief Turns ADC module on
 */
void ADCon(void){
    AD1CON1bits.ON = 1; // Enable A/D converter
}

/**
 * 
 * \brief Reads ADC in manual mode. 
 * Starts conversion and returns conversion value
 */
uint16_t ADCReadManual(void){
    // por enquanto nada
}

/**
 * \brief Reads ADC with automatic trigger (any mode different from SrcManual)
 * 
 * Requires previous configuration with ADCconfig(). 
 */
uint16_t ADCReadRetentive(void){
        AD1CON1bits.ASAM = 1; // Start conversion
        //while (IFS1bits.AD1IF == 0);
        while(IFS1bits.AD1IF == 0);
        return ADC1BUF0;
}

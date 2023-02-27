/**
 * \file:   analog.c
 * \author: anton
 *
 * \date 24 de Fevereiro de 2023, 17:35
 */

#include <xc.h>
#include <stdint.h>


//void ADCconfig(uint8_t SourceChannel, ADCTriggerSrc_t ConversionTriggerSource, uint8_t SampleTime){
    /* TRISB = (TRISB & 0x0) | (0x1 << SourceChannel);
    AD1PCFG = AD1PCFG & 0x0; // all RB ports configured as analog input 
    AD1CON2bits.VCFG = 0; // Voltage sources are AVdd and AVss
    
    AD1CON3bits.SAMC = SampleTime; // Sample time is 16 TAD (TAD = 100 ns)  ?? SampleTime é um tempo em nanosegundos????
    AD1CON1bits.SSRC = ConversionTriggerSource;
    
    AD1CHSbits.CH0SA = SourceChannel; //Positive Input Select bits for MUX A Multiplexer Setting
    AD1CON3bits.ADRC = 0; // ADC clock source is PB Clock
    AD1CON3bits.ADCS = 7; // ADC clock prescaler is set to 7
   */
   // no scanning of multiple inputs
//}

/**
 * \brief Turns ADC module off
 */
void ADCoff(void);

/**
 * \brief Turns ADC module on
 */
void ADCon(void);

/**
 * 
 * \brief Reads ADC in manual mode. 
 * Starts conversion and returns conversion value
 */
uint16_t ADCReadManual(void);

/**
 * \brief Reads ADC with automatic trigger (any mode different from SrcManual)
 * 
 * Requires previous configuration with ADCconfig(). 
 */
uint16_t ADCReadRetentive(void);

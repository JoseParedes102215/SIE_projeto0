/**
 * \file:   timer.c
 * \author: anton
 *
 * \date 20 de Fevereiro de 2023, 14:13
 */

#include <xc.h>
#include <stdint.h>
#include "timer.h"



const uint32_t TypeBTimerPreScalerVals[] = {1,2,4,8,16,32,64,256};
//const uint32_t TypeBTimerPreScalerVals[] = {1,2,4,8,16,32,64,256};


void Timer2Setup(bool TimerOn32bit, TypeBTimerPreScalers_t Prescaler, uint32_t PR2val){
    if(!TimerOn32bit){
        /*
          When TCS = 0:
    1 = Gated time accumulation is enabled
    0 = Gated time accumulation is disabled
         
         */
   
        //T2CONbits.TCS = 0;
        //T2CONbits.TGATE = 0; 
        PR2 = PR2val;
        T2CONbits.TCKPS = Prescaler;
       }
    else{
        //T2CONbits.TCS = 0;
        //T2CONbits.TGATE = 0;
        PR2 = PR2val;
        T2CONbits.TCKPS = Prescaler;
    }
}

void Timer2Start(void){
    //TMR2 = 0; // Timercounter2 = 0;
	T2CONbits.TON = 1; //Enable to Timer2
}


void Timer2Stop(void){
    T2CONbits.TON = 0; //Disable to Timer2 
}
/**
 * \brief Gets EOC flag from Timer2
 */
int Timer2GetEOC(void){
    return IFS0bits.T2IF;
    //return IFS0bits.T2IF; ????????????
}

/**
 * \brief Clears EOC flag of Timer2
 */
void Timer2ClearEOC(void){
    IFS0bits.T2IF = 0;
}

void Timer3Setup(TypeBTimerPreScalers_t Prescaler, uint32_t PR3val){
   
    
         
        //T3CONbits.TCS = 0;
        //T3CONbits.TGATE = 0;
        PR3 = PR3val;
        T3CONbits.TCKPS = Prescaler;
    
}


/**
 * \brief Starts Timer 3.
 */
void Timer3Start(void){
    T3CONbits.TON = 1; //Enable to Timer3
}


/**
 * \brief Stops Timer 3
 */
void Timer3Stop(void){
    T3CONbits.TON = 0; //Enable to Timer3
}



/**
 * \brief Gets EOC flag from Timer3
 */
int Timer3GetEOC(void){
    return IFS0bits.T3IF;
    
}

/**
 * \brief Clears EOC flag of Timer3
 */
void Timer3ClearEOC(void){
    IFS0bits.T3IF = 0;
    
}


/**
 * \brief Computes the configuration parameters (Prescaler and PR3 value) to configure 
 * a Type B Timer to generate events at frequency Freq_Hz (in Hz)
 * 
 * \param Freq_Hz       Desired frequency, in Hz
 * \param pPreScaler     Prescaler index (bits to be programmed in PSCK)
 * \param pPRxVal        Value for PRx 
 */
int TypeBTimer16bitGetConfigFromFreq(uint32_t Freq_Hz, TypeBTimerPreScalers_t *pPreScaler, uint32_t *pPRxVal){
    
    int pres_vals[] = {1,2,4,8,16,32,64,256};
    int i,kpres;
    kpres = PBCLK_F_HZ / (65536 * Freq_Hz);
    for( i = 0 ; i < 7 ; i++){
        if( kpres < pres_vals[i] ){
            kpres = pres_vals[i];
            *pPreScaler = kpres;
            *pPRxVal = ((PBCLK_F_HZ / *pPreScaler) / Freq_Hz) - 1;
            return 1;
        }
    }
    return 0;
}



/**
 * \brief Sets the counting frequency of a Type B Timer
 * 
 * If the requested frequency is not possible, the Timer registers are not 
 * changed and the function returns NOK. When the requested frequency is possible,
 * the Timer<i>x</i> (*x*=2..5) registers are set accordingly and the function 
 * returns OK. 
 * 
 * If some time number is not implemented, TypeBTimerSetFreq returns NOK
 * 
 * \param TimerNo   Number of Timer to configure
 * \param Freq_Hz   Requested frequency (in Hz)
 * \return          OK: sucess; NOK: failure
 */
int TypeBTimer16bitSetFreq(TypeBTimerNo_t TimerNo, uint32_t Freq_Hz){
    
    
    int pres_vals[] = {1,2,4,8,16,32,64,256};
    int i,kpres;
    kpres = PBCLK_F_HZ / (65536 * Freq_Hz);
    for( i = 0 ; i < 7 ; i++){
        if( kpres < pres_vals[i] ){
            kpres = pres_vals[i];
            switch(TimerNo){
                case 2:
                    T2CONbits.TCKPS = i;
                    PR2 = ((PBCLK_F_HZ / kpres) / Freq_Hz) - 1;
                    Timer2Start();
                    //PutChar('2');
                    break;
                case 3:
                    T3CONbits.TCKPS = i;
                    PR3 = ((PBCLK_F_HZ / kpres) / Freq_Hz) - 1;
                    Timer3Start();
                    break;
                case 4:
                    T4CONbits.TCKPS = i;
                    PR4 = ((PBCLK_F_HZ / kpres) / Freq_Hz) - 1;
                    T4CONbits.TON = 1;
                    break;
                case 5:
                    T5CONbits.TCKPS = i;
                    PR5 = ((PBCLK_F_HZ / kpres) / Freq_Hz) - 1;
                    T5CONbits.TON = 1;
                    break;
                default:
                    return NOK;
            }
            return OK;
        }
    }
}
    
    

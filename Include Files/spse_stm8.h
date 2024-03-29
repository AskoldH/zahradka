// V2.0 from 20.7.2022
#ifndef _SPSE_STM8_H_
#define _SPSE_STM8_H_ 1

#ifndef F_CPU

#warning F_CPU is not defined!
#endif

#include "stm8s_conf.h"
#include "delay.h"

#define ADC_TIMEOUT 1000
#define ADC_TSTAB 7 // �as pro stabilizaci ADC po zapnut� (7 us)

#ifdef STM8S208

uint16_t ADC_get(ADC2_Channel_TypeDef ADC2_Channel); // perform conversion on selected channel (ADC must be enabled prior calling that function)
void ADC2_Select_Channel(ADC2_Channel_TypeDef ADC2_Channel); // corrected function for selecting ADC channel
void ADC2_AlignConfig(ADC2_Align_TypeDef ADC2_Align); // configure ADC2 data align
void ADC2_Startup_Wait(void);

#endif

#if defined(STM8S103) || defined(STM8S105)

uint16_t ADC_get(ADC1_Channel_TypeDef ADC1_Channel); // perform conversion on selected channel (ADC must be enabled prior calling that function)
void ADC1_Select_Channel(ADC1_Channel_TypeDef ADC1_Channel); // corrected function for selecting ADC channel
void ADC1_AlignConfig(ADC1_Align_TypeDef ADC1_Align); // configure ADC1 data align
void ADC1_Startup_Wait(void);

#endif

// dod�lan� definice pro pr�ci s EEPROM s p�eklada�em Cosmic (p�ed z�pisem do EEPROM nezapome�te odem��t pomoc� FLASH_Unlock(FLASH_MEMTYPE_DATA);)
volatile char FLASH_CR2     @0x505b;    /* Flash Control Register 2 */
volatile char FLASH_NCR2    @0x505c;    /* Flash Complementary Control Reg 2 */
volatile char FLASH_IAPSR   @0x505f;    /* Flash in-appl Prog. Status reg */


#endif
   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
 195                     ; 49 uint16_t ADC_get(ADC1_Channel_TypeDef ADC1_Channel){
 197                     	switch	.text
 198  0000               _ADC_get:
 202                     ; 50 ADC1_Select_Channel(ADC1_Channel);
 204  0000 ad13          	call	_ADC1_Select_Channel
 206                     ; 51 ADC1->CR1 |= ADC1_CR1_ADON; // Start Conversion (ADON must be SET before => ADC must be enabled !)
 208  0002 72105401      	bset	21505,#0
 210  0006               L311:
 211                     ; 52 while(!(ADC1->CSR & ADC1_CSR_EOC));
 213  0006 c65400        	ld	a,21504
 214  0009 a580          	bcp	a,#128
 215  000b 27f9          	jreq	L311
 216                     ; 53 ADC1->CSR &=~ADC1_CSR_EOC;
 218  000d 721f5400      	bres	21504,#7
 219                     ; 54 return ADC1_GetConversionValue();
 221  0011 cd0000        	call	_ADC1_GetConversionValue
 225  0014 81            	ret
 270                     ; 57 void ADC1_Select_Channel(ADC1_Channel_TypeDef ADC1_Channel){
 271                     	switch	.text
 272  0015               _ADC1_Select_Channel:
 274  0015 88            	push	a
 275  0016 88            	push	a
 276       00000001      OFST:	set	1
 279                     ; 58     uint8_t tmp = (ADC1->CSR) & (~ADC1_CSR_CH);
 281  0017 c65400        	ld	a,21504
 282  001a a4f0          	and	a,#240
 283  001c 6b01          	ld	(OFST+0,sp),a
 285                     ; 59     tmp |= ADC1_Channel | ADC1_CSR_EOC;
 287  001e 7b02          	ld	a,(OFST+1,sp)
 288  0020 aa80          	or	a,#128
 289  0022 1a01          	or	a,(OFST+0,sp)
 290  0024 6b01          	ld	(OFST+0,sp),a
 292                     ; 60     ADC1->CSR = tmp;
 294  0026 7b01          	ld	a,(OFST+0,sp)
 295  0028 c75400        	ld	21504,a
 296                     ; 61 }
 299  002b 85            	popw	x
 300  002c 81            	ret
 355                     ; 63 void ADC1_AlignConfig(ADC1_Align_TypeDef ADC1_Align){
 356                     	switch	.text
 357  002d               _ADC1_AlignConfig:
 361                     ; 64 	if(ADC1_Align){
 363  002d 4d            	tnz	a
 364  002e 2708          	jreq	L761
 365                     ; 65 		ADC1->CR2 |= (uint8_t)(ADC1_Align);
 367  0030 ca5402        	or	a,21506
 368  0033 c75402        	ld	21506,a
 370  0036 2004          	jra	L171
 371  0038               L761:
 372                     ; 67 		ADC1->CR2 &= (uint8_t)(~ADC1_CR2_ALIGN);
 374  0038 72175402      	bres	21506,#3
 375  003c               L171:
 376                     ; 69 }
 379  003c 81            	ret
 405                     ; 71 void ADC1_Startup_Wait(void){
 406                     	switch	.text
 407  003d               _ADC1_Startup_Wait:
 411                     ; 23 	_asm("nop\n $N:\n decw X\n jrne $L\n nop\n ", __ticks);
 415  003d ae0026        	ldw	x,#38
 417  0040 9d            nop
 418  0041                L41:
 419  0041 5a             decw X
 420  0042 26fd           jrne L41
 421  0044 9d             nop
 422                      
 424  0045               L571:
 425                     ; 73 }
 428  0045 81            	ret
 441                     	xdef	_ADC1_Startup_Wait
 442                     	xdef	_ADC1_AlignConfig
 443                     	xdef	_ADC1_Select_Channel
 444                     	xdef	_ADC_get
 445                     	xref	_ADC1_GetConversionValue
 464                     	end

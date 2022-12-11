   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
  70                     	bsct
  71  0000               L33_time_wait:
  72  0000 00fa          	dc.w	250
  73  0002               L53_last_time:
  74  0002 0000          	dc.w	0
  75  0004               L73_last_time_uart:
  76  0004 0000          	dc.w	0
 107                     ; 15 void shine(void) {
 109                     	switch	.text
 110  0000               _shine:
 114                     ; 16 	GPIO_WriteReverse(GPIOD, GPIO_PIN_3);
 116  0000 4b08          	push	#8
 117  0002 ae500f        	ldw	x,#20495
 118  0005 cd0000        	call	_GPIO_WriteReverse
 120  0008 84            	pop	a
 121                     ; 17 	GPIO_WriteReverse(GPIOD, GPIO_PIN_4);
 123  0009 4b10          	push	#16
 124  000b ae500f        	ldw	x,#20495
 125  000e cd0000        	call	_GPIO_WriteReverse
 127  0011 84            	pop	a
 128                     ; 18 }
 131  0012 81            	ret
 134                     	bsct
 135  0006               L75_parameter:
 136  0006 0001          	dc.w	1
 171                     ; 21 void main(void){
 172                     	switch	.text
 173  0013               _main:
 177                     ; 22 CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovat MCU na 16MHz
 179  0013 4f            	clr	a
 180  0014 cd0000        	call	_CLK_HSIPrescalerConfig
 182                     ; 24 GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
 184  0017 4bc0          	push	#192
 185  0019 4b08          	push	#8
 186  001b ae500f        	ldw	x,#20495
 187  001e cd0000        	call	_GPIO_Init
 189  0021 85            	popw	x
 190                     ; 25 GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);
 192  0022 4bc0          	push	#192
 193  0024 4b10          	push	#16
 194  0026 ae500f        	ldw	x,#20495
 195  0029 cd0000        	call	_GPIO_Init
 197  002c 85            	popw	x
 198                     ; 27 init_milis();
 200  002d cd0000        	call	_init_milis
 202                     ; 23 	_asm("nop\n $N:\n decw X\n jrne $L\n nop\n ", __ticks);
 206  0030 ae0216        	ldw	x,#534
 208  0033 9d            nop
 209  0034                L01:
 210  0034 5a             decw X
 211  0035 26fd           jrne L01
 212  0037 9d             nop
 213                      
 215  0038               L36:
 216                     ; 29 uart1_init();
 218  0038 cd0000        	call	_uart1_init
 220  003b               L57:
 221                     ; 33 		if((milis() - last_time) > time_wait)
 223  003b cd0000        	call	_milis
 225  003e 72b00002      	subw	x,L53_last_time
 226  0042 b300          	cpw	x,L33_time_wait
 227  0044 23f5          	jrule	L57
 228                     ; 35 			last_time = milis();
 230  0046 cd0000        	call	_milis
 232  0049 bf02          	ldw	L53_last_time,x
 233                     ; 36 			shine();
 235  004b adb3          	call	_shine
 237                     ; 37 			send_str(int_to_str(parameter));
 239  004d be06          	ldw	x,L75_parameter
 240  004f cd0000        	call	_int_to_str
 242  0052 cd0000        	call	_send_str
 244  0055 20e4          	jra	L57
 279                     ; 45 void assert_failed(u8* file, u32 line)
 279                     ; 46 { 
 280                     	switch	.text
 281  0057               _assert_failed:
 285  0057               L121:
 286  0057 20fe          	jra	L121
 337                     	xdef	_main
 338                     	xdef	_shine
 339                     	xref	_int_to_str
 340                     	xref	_send_str
 341                     	xref	_uart1_init
 342                     	xref	_init_milis
 343                     	xref	_milis
 344                     	xdef	_assert_failed
 345                     	xref	_GPIO_WriteReverse
 346                     	xref	_GPIO_Init
 347                     	xref	_CLK_HSIPrescalerConfig
 366                     	end

   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
  45                     ; 3 void uart1_init(void)
  45                     ; 4 {
  47                     	switch	.text
  48  0000               _uart1_init:
  52                     ; 5     UART1_Init(
  52                     ; 6         9600, // rychlost
  52                     ; 7         UART1_WORDLENGTH_8D, // počet datových bitů
  52                     ; 8         UART1_STOPBITS_1, // stop bity
  52                     ; 9         UART1_PARITY_NO, // typ parity
  52                     ; 10         UART1_SYNCMODE_CLOCK_DISABLE, // synchonozační typ hodin
  52                     ; 11         UART1_MODE_TXRX_ENABLE // UART mode
  52                     ; 12     );
  54  0000 4b0c          	push	#12
  55  0002 4b80          	push	#128
  56  0004 4b00          	push	#0
  57  0006 4b00          	push	#0
  58  0008 4b00          	push	#0
  59  000a ae2580        	ldw	x,#9600
  60  000d 89            	pushw	x
  61  000e ae0000        	ldw	x,#0
  62  0011 89            	pushw	x
  63  0012 cd0000        	call	_UART1_Init
  65  0015 5b09          	addw	sp,#9
  66                     ; 14     UART1_Cmd(ENABLE);
  68  0017 a601          	ld	a,#1
  69  0019 cd0000        	call	_UART1_Cmd
  71                     ; 15 }
  74  001c 81            	ret
 110                     ; 17 void send_char(char c)
 110                     ; 18 {
 111                     	switch	.text
 112  001d               _send_char:
 114  001d 88            	push	a
 115       00000000      OFST:	set	0
 118  001e               L14:
 119                     ; 19      while (!UART1_GetFlagStatus(UART1_FLAG_TXE));
 121  001e ae0080        	ldw	x,#128
 122  0021 cd0000        	call	_UART1_GetFlagStatus
 124  0024 4d            	tnz	a
 125  0025 27f7          	jreq	L14
 126                     ; 20         UART1_SendData8(c);
 128  0027 7b01          	ld	a,(OFST+1,sp)
 129  0029 cd0000        	call	_UART1_SendData8
 131                     ; 21 }
 134  002c 84            	pop	a
 135  002d 81            	ret
 172                     ; 24 void send_str(char str[])
 172                     ; 25 {
 173                     	switch	.text
 174  002e               _send_str:
 176  002e 89            	pushw	x
 177       00000000      OFST:	set	0
 180                     ; 26     for (i2=0; str[i2]; i2++)
 182  002f ae0000        	ldw	x,#0
 183  0032 bf02          	ldw	L54_i2+2,x
 184  0034 ae0000        	ldw	x,#0
 185  0037 bf00          	ldw	L54_i2,x
 187  0039 200f          	jra	L17
 188  003b               L56:
 189                     ; 27         send_char(str[i2]);
 191  003b 1e01          	ldw	x,(OFST+1,sp)
 192  003d 92d602        	ld	a,([L54_i2+2.w],x)
 193  0040 addb          	call	_send_char
 195                     ; 26     for (i2=0; str[i2]; i2++)
 197  0042 ae0000        	ldw	x,#L54_i2
 198  0045 a601          	ld	a,#1
 199  0047 cd0000        	call	c_lgadc
 201  004a               L17:
 204  004a 1e01          	ldw	x,(OFST+1,sp)
 205  004c 926d02        	tnz	([L54_i2+2.w],x)
 206  004f 26ea          	jrne	L56
 207                     ; 28 }
 210  0051 85            	popw	x
 211  0052 81            	ret
 236                     ; 30 char get_char(void)
 236                     ; 31 {
 237                     	switch	.text
 238  0053               _get_char:
 242  0053               L701:
 243                     ; 32     while (!UART1_GetFlagStatus(UART1_FLAG_RXNE));
 245  0053 ae0020        	ldw	x,#32
 246  0056 cd0000        	call	_UART1_GetFlagStatus
 248  0059 4d            	tnz	a
 249  005a 27f7          	jreq	L701
 250                     ; 33     return UART1_ReceiveData8();
 252  005c cd0000        	call	_UART1_ReceiveData8
 256  005f 81            	ret
 338                     ; 39 const char* int_to_str(uint16_t integer)
 338                     ; 40 {	
 339                     	switch	.text
 340  0060               _int_to_str:
 342  0060 89            	pushw	x
 343  0061 522a          	subw	sp,#42
 344       0000002a      OFST:	set	42
 347                     ; 45     int pocet_cifer = 0;
 349  0063 5f            	clrw	x
 350  0064 1f29          	ldw	(OFST-1,sp),x
 353  0066 2045          	jra	L161
 354  0068               L551:
 355                     ; 52         if (!(integer % 10))
 357  0068 1e2b          	ldw	x,(OFST+1,sp)
 358  006a a60a          	ld	a,#10
 359  006c 62            	div	x,a
 360  006d 5f            	clrw	x
 361  006e 97            	ld	xl,a
 362  006f a30000        	cpw	x,#0
 363  0072 2610          	jrne	L561
 364                     ; 54             str_inverted[pocet_cifer] = '0';
 366  0074 96            	ldw	x,sp
 367  0075 1c0017        	addw	x,#OFST-19
 368  0078 1f03          	ldw	(OFST-39,sp),x
 370  007a 1e29          	ldw	x,(OFST-1,sp)
 371  007c 72fb03        	addw	x,(OFST-39,sp)
 372  007f a630          	ld	a,#48
 373  0081 f7            	ld	(x),a
 375  0082 201b          	jra	L761
 376  0084               L561:
 377                     ; 58             str_inverted[pocet_cifer] = (integer % 10) 
 377                     ; 59 						+ '0';
 379  0084 1e2b          	ldw	x,(OFST+1,sp)
 380  0086 a60a          	ld	a,#10
 381  0088 62            	div	x,a
 382  0089 5f            	clrw	x
 383  008a 97            	ld	xl,a
 384  008b 1c0030        	addw	x,#48
 385  008e 9096          	ldw	y,sp
 386  0090 72a90017      	addw	y,#OFST-19
 387  0094 1703          	ldw	(OFST-39,sp),y
 389  0096 1629          	ldw	y,(OFST-1,sp)
 390  0098 72f903        	addw	y,(OFST-39,sp)
 391  009b 01            	rrwa	x,a
 392  009c 90f7          	ld	(y),a
 393  009e 02            	rlwa	x,a
 394  009f               L761:
 395                     ; 61         integer /= 10;
 397  009f 1e2b          	ldw	x,(OFST+1,sp)
 398  00a1 a60a          	ld	a,#10
 399  00a3 62            	div	x,a
 400  00a4 1f2b          	ldw	(OFST+1,sp),x
 401                     ; 62         ++pocet_cifer;
 403  00a6 1e29          	ldw	x,(OFST-1,sp)
 404  00a8 1c0001        	addw	x,#1
 405  00ab 1f29          	ldw	(OFST-1,sp),x
 407  00ad               L161:
 408                     ; 50     while (integer > 0)
 410  00ad 1e2b          	ldw	x,(OFST+1,sp)
 411  00af 26b7          	jrne	L551
 412                     ; 65     str_inverted[pocet_cifer] = '/0' ;
 414  00b1 96            	ldw	x,sp
 415  00b2 1c0017        	addw	x,#OFST-19
 416  00b5 1f03          	ldw	(OFST-39,sp),x
 418  00b7 1e29          	ldw	x,(OFST-1,sp)
 419  00b9 72fb03        	addw	x,(OFST-39,sp)
 420  00bc a630          	ld	a,#48
 421  00be f7            	ld	(x),a
 422                     ; 67     for(i1 =0;  i1 < pocet_cifer;  i1++)
 424  00bf 5f            	clrw	x
 425  00c0 1f27          	ldw	(OFST-3,sp),x
 428  00c2 2027          	jra	L571
 429  00c4               L171:
 430                     ; 69         int index = (pocet_cifer -  i1) - 1;
 432  00c4 1e29          	ldw	x,(OFST-1,sp)
 433  00c6 72f027        	subw	x,(OFST-3,sp)
 434  00c9 5a            	decw	x
 435  00ca 1f05          	ldw	(OFST-37,sp),x
 437                     ; 70         str_final[ i1] = str_inverted[index];
 439  00cc 96            	ldw	x,sp
 440  00cd 1c0017        	addw	x,#OFST-19
 441  00d0 1f03          	ldw	(OFST-39,sp),x
 443  00d2 1e05          	ldw	x,(OFST-37,sp)
 444  00d4 72fb03        	addw	x,(OFST-39,sp)
 445  00d7 f6            	ld	a,(x)
 446  00d8 96            	ldw	x,sp
 447  00d9 1c0007        	addw	x,#OFST-35
 448  00dc 1f01          	ldw	(OFST-41,sp),x
 450  00de 1e27          	ldw	x,(OFST-3,sp)
 451  00e0 72fb01        	addw	x,(OFST-41,sp)
 452  00e3 f7            	ld	(x),a
 453                     ; 67     for(i1 =0;  i1 < pocet_cifer;  i1++)
 455  00e4 1e27          	ldw	x,(OFST-3,sp)
 456  00e6 1c0001        	addw	x,#1
 457  00e9 1f27          	ldw	(OFST-3,sp),x
 459  00eb               L571:
 462  00eb 9c            	rvf
 463  00ec 1e27          	ldw	x,(OFST-3,sp)
 464  00ee 1329          	cpw	x,(OFST-1,sp)
 465  00f0 2fd2          	jrslt	L171
 466                     ; 73     str_final[pocet_cifer] = '\0';
 468  00f2 96            	ldw	x,sp
 469  00f3 1c0007        	addw	x,#OFST-35
 470  00f6 1f03          	ldw	(OFST-39,sp),x
 472  00f8 1e29          	ldw	x,(OFST-1,sp)
 473  00fa 72fb03        	addw	x,(OFST-39,sp)
 474  00fd 7f            	clr	(x)
 475                     ; 75     return (str_final);
 477  00fe 96            	ldw	x,sp
 478  00ff 1c0007        	addw	x,#OFST-35
 481  0102 5b2c          	addw	sp,#44
 482  0104 81            	ret
 506                     	switch	.ubsct
 507  0000               L54_i2:
 508  0000 00000000      	ds.b	4
 509                     	xdef	_int_to_str
 510                     	xdef	_get_char
 511                     	xdef	_send_str
 512                     	xdef	_send_char
 513                     	xdef	_uart1_init
 514                     	xref	_UART1_GetFlagStatus
 515                     	xref	_UART1_SendData8
 516                     	xref	_UART1_ReceiveData8
 517                     	xref	_UART1_Cmd
 518                     	xref	_UART1_Init
 538                     	xref	c_lgadc
 539                     	end

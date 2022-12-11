// Vzorový projekt pro STM8S103F
#include "stm8s.h"
#include "delay.h"
#include "milis.h"
#include "spse_stm8.h"
#include "stm8s_uart1.h"
#include "uart.h"
//#include "stm8_hd44780.h"

static uint16_t time_wait=250;
static uint16_t last_time=0;
static uint16_t last_time_uart=0;


void shine(void) {
	GPIO_WriteReverse(GPIOD, GPIO_PIN_3);
	GPIO_WriteReverse(GPIOD, GPIO_PIN_4);
}

static uint16_t parameter = 2;
void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovat MCU na 16MHz

GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);

init_milis();
_delay_us(100);
uart1_init();

  while (1)
	{
		if((milis() - last_time) > time_wait)
		{
			last_time = milis();
			shine();
			send_str(int_to_str(parameter));
		}
	}
}



#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line)
{ 
  while (1)
  {
  }
}
#endif
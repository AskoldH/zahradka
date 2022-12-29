// Vzorový projekt pro STM8S103F
#include "stm8s.h"
#include "delay.h"
#include "milis.h"
#include "spse_stm8.h"
#include "stm8s_uart1.h"
#include "uart.h"
#include "swi2c.h"

// time values for milis
static uint16_t read_temp_period=2000;
static uint16_t last_time_temp=0;

// ventil on/off (now is kinda useless, let's see if we need it later)
static uint8_t ventil_on = 0;

// i2c sht30 address
#define SH30_SLVADR (0b1000100) 

// data from sht30 temperature and humidity sensor, 
//[0] -> temperature (3 decimal place), [1] -> humidity
static int16_t sht30_temp_and_hmd[1]; 

// reverse on bord led for signalization
void reverse_led(void) {
	GPIO_WriteReverse(GPIOD, GPIO_PIN_4);
}

// open / close ventil, GPIO D3
void reverse_ventil(void) {
	GPIO_WriteReverse(GPIOD, GPIO_PIN_3);
}

void send_temp_and_hmd_sht30(void){
	// sends tempeture
	send_str("Tempeture: ");
	send_str(int_to_str(sht30_temp_and_hmd[0]));
	send_str("\n\r");
	
	// sends humidity
	send_str("Humidity: ");
	send_str(int_to_str(sht30_temp_and_hmd[1]));	
	send_str(" %\n\r");
}			

void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovat MCU na 16MHz

// init section
GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW); // on-board led
GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW); // ventil GPIO
init_milis();
uart1_init();
swi2c_init();
_delay_us(100);

  while (1)
	{
		// read and send sh30 values
		if((milis() - last_time_temp) > read_temp_period)
		{
			last_time_temp = milis();
			
			// get tempeture and humidity values into sht30_temp_and_hmd 
			// variable, [0]-> tempeture, [1]-> humidity
			sht30_get_temp_and_hmd(SH30_SLVADR, sht30_temp_and_hmd);
			
			// sends temperature and humidity via uart
			send_temp_and_hmd_sht30();
			
			// led on -> ventil open
			reverse_ventil();
			reverse_led();
		}
		
		// toggle ventil on/off
		/*if((milis() - last_time_ventil) > toggle_ventil_period){
			last_time_ventil = milis();
			
			reverse_ventil();
			// led on -> ventil open
			reverse_led();
			
			if (ventil_on == 1){
				ventil_on=0;
			}
			else{
				ventil_on=1;
			}
		}*/
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
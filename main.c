// Vzorový projekt pro STM8S103F
#include "stm8s.h"
#include "delay.h"
#include "milis.h"
#include "spse_stm8.h"
#include "stm8s_uart1.h"
#include "uart.h"
#include "swi2c.h"

#define MEMORY_I2C_ADDR (0b1010111)
#define SH30_I2C_ADDR (0b1000100)

// senzor vlhkosti pudy
uint16_t lk;
void ADC_init(void);


// time values for milis
static uint16_t read_temp_period=2000;
static uint16_t last_time_temp=0;

// ventil on/off (now is kinda useless, let's see if we need it later)
static uint8_t ventil_on = 0; 

// data from sht30 temperature and humidity sensor, 
//[0] -> temperature (3 decimal place), [1] -> humidity
static int16_t sht30_temp_and_hmd[2]; 

// data to write to the external EEPROM memory
uint8_t data_to_write[4] = {2, 3, 4, 6}; 

// read data from the external EEPROM memory
uint8_t read_data[4];

// for mapping memory block 0-4096 available 
uint16_t last_memory_addr = 0;

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

INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
	reverse_led();
	send_char('a');
}

void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovat MCU na 16MHz

// init section
GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW); // on-board led
// TODO zmenit ventil GPIO -> tohle je pro AIN4
//GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW); // ventil GPIO

// interrupt init
/*GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_FL_IT);
EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD,EXTI_SENSITIVITY_FALL_ONLY);
ITC_SetSoftwarePriority(ITC_IRQ_PORTD,ITC_PRIORITYLEVEL_1);
*/
init_milis();
uart1_init();
swi2c_init();
_delay_us(100);

//enableInterrupts();

ADC_init();
send_str("\r\n\r\n");
send_str("Started...");
send_str("\r\n");

// writing data to EEPROM example
send_str(int_to_str(write_to_EEPROM(data_to_write, last_memory_addr, MEMORY_I2C_ADDR)));

// reading data from EEPROM example
send_str(int_to_str(read_from_EEPROM(read_data, last_memory_addr, MEMORY_I2C_ADDR)));

  while (1)
	{
		// read and send sh30 values
		if((milis() - last_time_temp) > read_temp_period)
		{
			last_time_temp = milis();
			
			//vlhkost pudy poslani uart
			lk = ADC_get(ADC1_CHANNEL_4);
			send_str("Hodnota vlhkosti: ");
			send_str(int_to_str(lk));
			send_str("\r\n");
	
			// get tempeture and humidity values into sht30_temp_and_hmd 
			// variable, [0]-> tempeture, [1]-> humidity
			//sht30_get_temp_and_hmd(SH30_I2C_ADDR, sht30_temp_and_hmd);
			
			// sends temperature and humidity via uart
			//send_temp_and_hmd_sht30();
			
			// led on -> ventil open
			//reverse_ventil();
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

// inicializace ADC 
void ADC_init(void){
// na pinech/vstupech ADC_IN2 (PB2) a ADC_IN3 (PB3) vypneme vstupní buffer

// channel 1 = GPIOB, GPIO_PIN_0 -> tohle je blbost
//ADC1_SchmittTriggerConfig(ADC1_SCHMITTTRIG_CHANNEL1,DISABLE);
// channel 2 = GPIOC, GPIO_PIN_4
ADC1_SchmittTriggerConfig(ADC1_SCHMITTTRIG_CHANNEL4,DISABLE);
// nastavíme clock pro ADC (16MHz / 4 = 4MHz)
ADC1_PrescalerConfig(ADC1_PRESSEL_FCPU_D4);
// volíme zarovnání výsledku (typicky vpravo, jen vyjmecne je výhodné vlevo)
ADC1_AlignConfig(ADC1_ALIGN_RIGHT);
// nasatvíme multiplexer na nekterý ze vstupních kanálu
ADC1_Select_Channel(ADC1_CHANNEL_4);
// rozbehneme AD prevodník
ADC1_Cmd(ENABLE);
}

#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line)
{ 
  while (1)
  {
  }
}
#endif
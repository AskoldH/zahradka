#ifndef __STM8_SWI2C_H
#define __STM8_SWI2C_H

// Software (bit bang) Master I2C library V1.0
#include "stm8s_conf.h"
#include "delay.h"

// ---- USER EDIT SECTION ----
// select GPIOs
#define SCL_GPIO GPIOB
#define SCL_PIN GPIO_PIN_4
#define SDA_GPIO GPIOB
#define SDA_PIN GPIO_PIN_5

// coarse timing parameters (~us) 
#define SWI2C_START_STOP_TIME 5
#define SWI2C_SDA_SETUP_TIME 5
#define SWI2C_SDA_HOLD_TIME 5
#define SWI2C_SCL_HALFPERIOD_TIME 5
// timeouts
#define SWI2C_TIMEOUT 0xffff // maximum number of waiting cycles

// ---- NO EDIT SECTION ----

#define SCL_stat() GPIO_ReadInputPin(SCL_GPIO,SCL_PIN)
#define SDA_stat() GPIO_ReadInputPin(SDA_GPIO,SDA_PIN)

#define SCL_HIGH GPIO_WriteHigh(SCL_GPIO,SCL_PIN)
#define SCL_LOW GPIO_WriteLow(SCL_GPIO,SCL_PIN)
#define SDA_HIGH GPIO_WriteHigh(SDA_GPIO,SDA_PIN)
#define SDA_LOW GPIO_WriteLow(SDA_GPIO,SDA_PIN)

#define SWI2C_SS_TIME _delay_us(SWI2C_START_STOP_TIME)
#define SWI2C_SETUP_TIME _delay_us(SWI2C_SDA_SETUP_TIME)
#define SWI2C_HOLD_TIME _delay_us(SWI2C_SDA_HOLD_TIME)
#define SWI2C_SCL_HIGH_TIME _delay_us(SWI2C_SCL_HALFPERIOD_TIME)

// user functions
void swi2c_init(void); // init GPIOs as Open Drain outputs
uint8_t swi2c_test_slave(uint8_t slvaddr); // check if slave with selected adres is present on bus
uint8_t swi2c_recover(void);

uint8_t sht30_get_temp_and_hmd(uint8_t slvaddr, int16_t* sht30_temp_and_hmd);
uint8_t sht30_set_data(uint8_t slvaddr);
uint8_t sht30_get_data(uint8_t slvaddr, uint8_t* sht30data);
	
// private functions
uint8_t swi2c_writebit(uint8_t bit);
uint8_t swi2c_readbit(void);
uint8_t swi2c_START(void);
uint8_t swi2c_RESTART(void);
uint8_t swi2c_STOP(void);



#endif /* __STM8_SWI2C_H*/
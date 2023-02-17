#include "swi2c.h"

// writes 4 bytes from data_to_write list to EEPROM memory
// position starts of data starts with memory_block_addr
uint8_t write_to_EEPROM(uint8_t* data_to_write, uint16_t memory_block_addr, uint8_t slv_addr){
	uint8_t i, ack, mask;
	uint8_t memory_addr_MSB = memory_block_addr>>8;
	uint8_t memory_addr_LSB = memory_block_addr;
	
	// stupid delay function to secure normal function
	uint16_t j;
	for(j=0; j < 30000; j++){}
	
	// start
	if(swi2c_START()){return 0xaa;}
	
	// send address
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(slv_addr<<1 & mask)){return 0xff;}
		mask = mask >>1;
	}
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// send memory address MSB byte
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(memory_addr_MSB & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// send memory address LSB byte
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(memory_addr_LSB & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	for(i=0; i < 4; i++){
		// send data_to_write
		mask=0b1<<7;
		while(mask){
			if(swi2c_writebit(data_to_write[i] & mask)){return 0xff;}
			mask = mask >>1;
		}
		// ack
		ack=swi2c_readbit();
		if(ack){
			if(swi2c_STOP()){return 0xff;}
			return ack;
			}
	}
	
	// stop
	if(swi2c_STOP()){return 0xff;}
	return 0;
}

// reads 4 bytes from EEPROM and saves it into read_data
// starts reading from position memory_block_addr
uint8_t read_from_EEPROM(uint8_t* read_data,  uint16_t memory_block_addr, uint8_t slv_addr){
	uint8_t i, mask, ack, bit; 
	uint8_t memory_addr_LSB = memory_block_addr;
	uint8_t memory_addr_MSB = memory_block_addr>>8;
	
	// stupid delay function to secure normal function
	uint16_t j;
	for(j=0; j < 30000; j++){}
	
	// start
	if(swi2c_START()){return 0xaa;}
	
	// send address
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(slv_addr<<1 & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// send memory address MSB byte
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(memory_addr_MSB & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// send memory address LSB byte
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(memory_addr_LSB & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// stop
	if(swi2c_STOP()){return 0xff;}
	
	// start
	if(swi2c_START()){return 0xaa;}
	
	// send address
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(((slv_addr<<1)|1) & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	// ack
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// read data 
	for(i=0; i<4; i++){
		mask=0b1<<7;
		while(mask){
			bit = swi2c_readbit();
			if(bit==0){read_data[i] &=~mask;}
			else if(bit==1){read_data[i] |=mask;}
			else{swi2c_STOP();return 0xff;}
			mask = mask >>1;
			}
		if(i==3){swi2c_writebit(1);}
		else{swi2c_writebit(0);}
	}
	
	// stop
	if(swi2c_STOP()){return 0xff;}
	return 0;
}

uint8_t sht30_set_data(uint8_t slvaddr){
	uint8_t i;	
	uint8_t ack;
	uint8_t mask;
	uint8_t command_msb = 0x2C;
	uint8_t command_lsb = 0x06;
	
	slvaddr = slvaddr<<1;
	// --- Generate START ---
	if(swi2c_START()){return 0xaa;}
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(slvaddr & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(command_msb & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(command_lsb & mask)){return 0xff;}
		mask = mask >>1;
	}
	
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	// --- STOP ---
	if(swi2c_STOP()){return 0xff;}
	return 0;
}

uint8_t sht30_get_data(uint8_t slvaddr, uint8_t* sht30data){
	uint8_t i=0, bit;	
	uint8_t ack;
	uint8_t mask;
	sht30_set_data(slvaddr);
	
	_delay_us(1000);
	
	slvaddr = (slvaddr<<1)+1;
	// --- Generate START ---
	if(swi2c_START()){return 0xaa;} 	
	
	
	mask=0b1<<7;
	while(mask){
		if(swi2c_writebit(slvaddr & mask)){return 0xff;}
		mask = mask >>1;
	}
	ack=swi2c_readbit();
	if(ack){
		if(swi2c_STOP()){return 0xff;}
		return ack;
	}
	
	for(i=0;i<5;i++){
		if(i < 2){
			mask=0b1<<7;
				while(mask){
					bit = swi2c_readbit();
						if(bit==0){
							sht30data[i] &=~mask;
						}
						else if(bit==1){
							sht30data[i] |=mask;
							}
						else{
							swi2c_STOP();return 0xff;
						}
						mask = mask >>1;
				}
			swi2c_writebit(0);
		}
		else if(i==2){
			mask=0b1<<7;
			while(mask){
				bit = swi2c_readbit();
					if(bit==0){
						//humidity[i] &=~mask;
					}
					else if(bit==1){
						//humidity[i] |=mask;
						}
					else{
						swi2c_STOP();return 0xff;
					}
					mask = mask >>1;
			}
			swi2c_writebit(0);
		}
		else{
			mask=0b1<<7;
			while(mask){
				bit = swi2c_readbit();
					if(bit==0){
						sht30data[i-1] &=~mask;
					}
					else if(bit==1){
						sht30data[i-1] |=mask;
						}
					else{
						swi2c_STOP();return 0xff;
					}
					mask = mask >>1;
			}
			if(i==4){swi2c_writebit(1);}
			else{swi2c_writebit(0);}
		}
	}
	
	// --- STOP ---
	if(swi2c_STOP()){return 0xff;}
	return 0;
}

uint8_t sht30_get_temp_and_hmd(uint8_t slvaddr, int16_t* sht30_temp_and_hmd){
	uint8_t sht30data[3];
	
	sht30_get_data(slvaddr, sht30data);
	sht30_temp_and_hmd[0] = (((((sht30data[0]<<8 | sht30data[1])/65535.0)*175))*1000)/1;
	sht30_temp_and_hmd[0] = sht30_temp_and_hmd[0]-45000;
	sht30_temp_and_hmd[1] = (((sht30data[2] << 8 | sht30data[3])/65535.0)*100)/1;
	return 0;
}
// test (ACK/NACK) of selected I2C slave address (like a ping - testing slave present on bus)
// slave address in 8bit representation (left aligned 7bit value)
// returns 0 if is slave present on bus
// returns 1 if slave is not present on bus
// returns 0xff if timeout error
// returns 0xaa if busy bus
uint8_t swi2c_test_slave(uint8_t slvaddr){
uint8_t ack;
uint8_t mask=0b1<<7;
if(swi2c_START()){return 0xaa;}
while(mask){
if(swi2c_writebit(slvaddr & mask)){return 0xff;}
mask = mask >>1;
}
ack=swi2c_readbit();
if(swi2c_STOP()){return 0xff;}
return ack;
}

// initialise SDA and SCL pins to Outputs with Open Drain
void swi2c_init(void){
GPIO_Init(SCL_GPIO,SCL_PIN,GPIO_MODE_OUT_OD_HIZ_SLOW);
GPIO_Init(SDA_GPIO,SDA_PIN,GPIO_MODE_OUT_OD_HIZ_SLOW);
}

// --- Private functions ---

// read bit value from bus
// returns 0 if read 0
// returns 1 if read 1
// returns 0xff if timeout condition
uint8_t swi2c_readbit(void){
uint16_t timeout=SWI2C_TIMEOUT;
uint8_t retval;
SDA_HIGH; // release SDA
SWI2C_SETUP_TIME;
SCL_HIGH;
while(SCL_stat() == RESET && timeout){timeout--;}
if(timeout==0){return 0xff;}
SWI2C_SCL_HIGH_TIME;
if(SDA_stat() == RESET){retval = 0;}else{retval=1;}
SCL_LOW;
SWI2C_HOLD_TIME; // hold time
return retval;
}

// write one bit on bus
// returns 0xff if SCL line blocked (timeout)
// returns 0 if success
uint8_t swi2c_writebit(uint8_t bit){
uint16_t timeout=SWI2C_TIMEOUT;
if(bit){SDA_HIGH;}else{SDA_LOW;} // set desired SDA value
SWI2C_SETUP_TIME; // setup time
SCL_HIGH;		
while(SCL_stat() == RESET && timeout){timeout--;} // wait until SCL is not high
if(timeout==0){SDA_HIGH; return 0xff;} // generate timeout error if SCL is held Low too long
SWI2C_SCL_HIGH_TIME;
SCL_LOW;
SWI2C_HOLD_TIME; // hold time
return 0;
}

// generate RESTART bit
// returns 1 if bus is busy (SDA or SCL is Low)
// return 0 if success
/*uint8_t swi2c_RESTART(void){
uint16_t timeout=SWI2C_TIMEOUT;
SCL_LOW;
SDA_HIGH;
while(SDA_stat() == RESET && timeout){timeout--;}
if(timeout==0){SCL_HIGH; return 0xff;}
SWI2C_SS_TIME;
SCL_HIGH;
while(SCL_stat() == RESET && timeout){timeout--;}
if(timeout==0){return 0xff;}
SWI2C_SS_TIME;
SDA_LOW;
SWI2C_SS_TIME;
SCL_LOW;
SWI2C_SS_TIME;
return 0;
}*/

// generate START bit
// returns 0xff if bus is busy (SDA or SCL is Low)
// return 0 if success
uint8_t swi2c_START(void){
uint16_t timeout=SWI2C_TIMEOUT;
while((SCL_stat() == RESET || SDA_stat() == RESET) && timeout){timeout--;}
if(timeout == 0){return 0xff;}
//if(SCL_stat() == RESET || SDA_stat() == RESET){SDA_HIGH; SCL_HIGH; return 0xff;}
SDA_LOW;
SWI2C_SS_TIME;
SCL_LOW;
SWI2C_SS_TIME;
return 0;
}

// generate STOP bit
// return 0xff if timeout error (SCL is held low too long)
// return 0 if success
uint8_t swi2c_STOP(void){
uint16_t timeout=SWI2C_TIMEOUT;
uint8_t retval = 0;
SDA_LOW;
SWI2C_SS_TIME;
SCL_HIGH;
while(SCL_stat() == RESET && timeout){timeout--;}
if(timeout==0){retval = 0xff;}
SWI2C_SS_TIME;
SDA_HIGH;
return retval;
}

// Try to recover bus from failure
// returns 0 if bus is free (success)
// returns 0xff if SCL is hold low too long
// returns 0xee if SDA is still held low 
/*uint8_t swi2c_recover(void){
uint16_t timeout=SWI2C_TIMEOUT;
uint8_t i;
SCL_HIGH; // release both lines
SDA_HIGH;
SWI2C_SETUP_TIME;
// if both lines are High => everything OK, Bus is free
if(SCL_stat() != RESET && SDA_stat() != RESET){return 0;}
// if some slave holds SDA in LOW
if(SDA_stat() == RESET){
	for(i=0;i<9;i++){ // try nine times try to read one bit and pray for SDA release
		SCL_LOW;
		SWI2C_HOLD_TIME; 
		SCL_HIGH; 
		while(SCL_stat() == RESET && timeout){timeout--;}
		if(timeout==0){return 0xff;}
		SWI2C_SCL_HIGH_TIME; 
		if(SDA_stat() != RESET){ // if slave released SDA line, generate STOP
			return(swi2c_STOP());
			}
		}
		return 0xee;
	}
}*/



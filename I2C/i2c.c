#include "peripherals.h"

#include <stdio.h>
#include <interrupt.h>

#include "i2c.h"

#define SRF02_address				0xE0
#define SRF02_command_reg			0x00
#define SRF02_measurement_high_reg		0x02
#define SRF02_measurement_low_reg		0x03
#define SRF02_start_measurement_command		0x51

volatile char isReady = 0;

void i2c_master_enable(i2c_master_regs_t *i2c, unsigned char div) {
	i2c->ctrl = I2C_CTRL_EN | div;  			//div 299 for 60MHZ
}

int i2c_master_write(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned char data) {
	i2c->data[0] = address;	
	i2c->data[1] = reg;		//transmit address
	i2c->data[2] = data;
	i2c->cmd = I2C_CMD_STA|I2C_CMD_STO|(3 << 3);			//set start and write bits
	while(i2c->stat & I2C_STA_TIP);				//wait for transmission to finish
	if(i2c->stat & I2C_STA_NO_ACK) return -1;	//leave if acknowledgment failed
	return 0;
}

void i2c_master_handle_interrupt(i2c_master_regs_t *i2c){
	i2c->cmd = I2C_CTRL_INTR_EN;

}

// interrupt code
void i2c_master_write_interrupt(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned char data) {
	i2c->data[0] = address;	
	i2c->data[1] = reg;		
	i2c->data[2] = data;
	i2c->cmd = I2C_CMD_STA|I2C_CMD_STO|(3 << 3);
	i2c->cmd = I2C_CTRL_INTR_EN;				
	while(i2c->stat & I2C_STA_TIP){
		i2c_master_handle_interrupt(i2c);
	};
}



unsigned char i2c_master_read(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned char *ret) {

	i2c->data[0] = address;				//transmit address
	i2c->cmd = I2C_CMD_STA|(1 << 3);			//set start and write bits
	while(i2c->stat & I2C_STA_TIP);				//wait for transmission to finish
	if(i2c->stat & I2C_STA_NO_ACK) return -1;	//leave if acknowledgment failed

	i2c->data[1] = reg;							//transmit register to be written to
	i2c->cmd = I2C_CMD_STO|(1 << 3);			//set write bit
	while(i2c->stat & I2C_STA_TIP);				//wait for transmission to finish
	if(i2c->stat & I2C_STA_NO_ACK) return -1;	//leave if acknowledgment failed

	i2c->data[0] = (address) + 1;						//transmit read address
	i2c->cmd = I2C_CMD_RD|I2C_CMD_STA|(1 << 3);			//set write bit
	while(i2c->stat & I2C_STA_TIP);							//wait for transmission to finish
	if(i2c->stat & I2C_STA_NO_ACK) return -1;				//leave if acknowledgment failed

	i2c->cmd = I2C_CMD_RD|I2C_CMD_STO ;			//set write, read and stop bits
	while(i2c->stat & I2C_STA_TIP);					//wait for transmission to finish
	*ret = i2c->data[1];
printf("revision :%x \n", i2c->data[1]);

	return 0;
}

unsigned char i2c_master_read2bytes(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned int *ret) {

	i2c->data[0] = address;	
	i2c->data[1] = reg;			//transmit address
	i2c->cmd = I2C_CMD_STA|(2 << 3);			//set start and write bits
	while(i2c->stat & I2C_STA_TIP);				//wait for transmission to finish
	if(i2c->stat & I2C_STA_NO_ACK) return -1;	//leave if acknowledgment failed

	i2c->data[0] = (address) + 1;			//transmit read address
	i2c->cmd = I2C_CMD_RD|I2C_CMD_STA|I2C_CMD_STO|(5 << 3);	// änderung!!!!!	//set write bit
	while(i2c->stat & I2C_STA_TIP);				//wait for transmission to finish
	if(i2c->stat & I2C_STA_NO_ACK) return -1;	//leave if acknowledgment failed	

	*ret = (i2c->data[1] << 8);		//get high byte
	*ret |= i2c->data[2];			//get low byte

//printf("Register 1:%x \n", i2c->data[0]);
//printf("Register 2:%x \n", i2c->data[1]);
//printf("Register 3:%x \n", i2c->data[2]);
//printf("Register 4:%x \n", i2c->data[3]);
//printf("Register 5:%x \n", i2c->data[4]);

	return 0;
}

void SRF02_start_measurement(void) {
    //i2c_master_write(&I2C_MASTER_0, SRF02_address, SRF02_command_reg, SRF02_start_measurement_command);
	i2c_master_write_interrupt(&I2C_MASTER_0, SRF02_address, SRF02_command_reg, SRF02_start_measurement_command);
}

unsigned char SRF02_read_revision(void) {
	unsigned char ret = 0xFF;
    i2c_master_read(&I2C_MASTER_0, SRF02_address, SRF02_command_reg, &ret);
	return ret;
}

unsigned int SRF02_get_measurement(void) {
	unsigned int ret = 0;
    i2c_master_read2bytes(&I2C_MASTER_0, SRF02_address, SRF02_measurement_high_reg, &ret);
	return ret;
}







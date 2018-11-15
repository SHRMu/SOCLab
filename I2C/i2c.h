#ifndef I2C_H_
#define I2C_H_

#include "peripherals.h"

void i2c_master_enable(i2c_master_regs_t *i2c, unsigned char div);
int i2c_master_write(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned char data);
unsigned char i2c_master_read(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned char *data);
unsigned char i2c_master_read2bytes(i2c_master_regs_t *i2c, unsigned char address, unsigned char reg, unsigned int *data);

unsigned char SRF02_read_revision(void);
void SRF02_start_measurement(void);
unsigned int SRF02_get_measurement(void);

#endif

#include "peripherals.h"
		
#include <uart.h>
#include <stdio.h>
#include <sleep.h>

#include <spi.h>

#include "spi_local.h"

void spi_peri_enable(spi_master_regs_t *spi) {
	//CPOL = 1
    SET(spi->spi.spi_control, SPI_MASTER_CTRL_CPOL);
    //CPAH = 1
    SET(spi->spi.spi_control, SPI_MASTER_CTRL_CPHA);
	//set the frame width to 9
	SET(spi->spi.spi_control, (9 << 8) & SPI_MASTER_CTRL_BITCNT);
	//SCLK = (clk_peri) / (4 * divider) 
	//60MHz/(4*2) < 10MHz with divider 1
	SET(spi->spi.spi_control, (1 << 13) & SPI_MASTER_CTRL_DIV); 
	//enable the spi master
	SET(spi->spi.spi_control, SPI_MASTER_CTRL_EN);
}

void spi_peri_write(spi_master_regs_t *spi, unsigned int data) {

	while((spi->spi.spi_status&SPI_MASTER_STAT_FILL)!=0);
	//send data to slave
	spi->spi.spi_data_out = data;

	while((spi->spi.spi_status&SPI_MASTER_STAT_FILL)!=0);
	
}

void spi_peri_select(spi_master_regs_t *spi) {
	//activate the slave 1
	spi->spi.spi_control |= 1<<4;
}	

void spi_peri_deselect(spi_master_regs_t *spi) {	
	//deactivate the slave 1
	spi->spi.spi_control &= ~SPI_MASTER_CTRL_SLAVE;
}

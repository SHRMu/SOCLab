#ifndef __INCLUDE_SPI
#define __INCLUDE_SPI

#include "peripherals.h"

#include <spi.h>

void spi_peri_enable(spi_master_regs_t *spi);
void spi_peri_write(spi_master_regs_t *spi, unsigned int data);
void spi_peri_select(spi_master_regs_t *spi);
void spi_peri_deselect(spi_master_regs_t *spi);

#endif

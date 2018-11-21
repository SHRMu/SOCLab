
#include "peripherals.h"

#include <uart.h>
#include <stdio.h>
#include <sleep.h>
#include <interrupt.h>

#include "i2c.h"

void test_SFR02() {

	int dis = 0;
	//while(1){
	interrupt_enable();
	for(int i=0; i<5; i++) {
		SRF02_start_measurement();			//Start measurement
		sleep(130000);
		printf("read revision...\n");			
		//while(SRF02_read_revision() > 254);		//Wait for measurement to start
		printf("distance measurement...\n");
		dis = SRF02_get_measurement();			//get measurement
		printf("distance: %d\n", dis);
	}
}


FILE * stdout = &UART_LIGHT_0_FILE;

void main() {

	printf("Hello Sp601 SRF02\n");
	i2c_master_enable(&I2C_MASTER_0, 299);
	printf("i2c enabled\n");
	//sleep(200000);
	test_SFR02();

}

ISR(0)(){
	printf("interrupt starting ....");
	sleep(130000);
}




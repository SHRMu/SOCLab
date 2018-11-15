# SOCLab

SOCLab Code for the Lecture RS2 in TU Darmstadt

The following steps can be considered to help your SOCLab with SpartanMC SOC-Kit

##### Create a SpartanMC project #####

- cd $SPARTANMC_ROOT
- make newproject +path=~/Desktop/newproject

##### Create firmware & Open JConfig #####

Under project directory:
- make newfirmware +path=firmware
- (module load jdk/OpenJDK11/11.0.1)
- make jconfig

##### Customizing the SpartanMC System #####

Select components:
- SP601
- SpartanMC core
- UART Light

##### Example Code #####

 #include "peripherals.h"
 #include <stdio.h>

 FILE * stdout = &UART_LIGHT_0_FILE;

 void main() {
	printf("hello world\n");\n
 }

##### Connect to USB UART port #####

- stty -F /dev/ttyUSB0 115200 cs8 -echo raw
- cat /dev/ttyUSB0

##### Load the Code #####

- make all program (make updateRam program)

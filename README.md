# SOCLab

SOCLab for Lecture RS2 in TU Darmstadt

The following steps can be considered to help your SOCLab with SpartanMC SOC-Kit

##### Create a SpartanMC project #####

- cd $SPARTANMC_ROOT
- make newproject +path=/path/to/new/project

##### Create firmware & Open JConfig #####

Under project directory:
- make newfirmware +path=firmware
(module load jdk/OpenJDK11/11.0.1)
- make jconfig

##### Customizing the SpartanMC System #####

Select components:
- SP601
- SpartanMC core
- UART Light
# EchoCar

Hi there, my name is Victor. I'm a ~~undergraduate~~ graduated computer engineer, currently working as a firmware trainee engineer. The EchoCar is my final paper project for college.

I used two microcontrollers: a Bluepill (STM32F103C8T6) to control the hardware itself and an Arduino Nano 33 BLE Sense to run the MFCC algorithm and the AI model. I chose to use Zephyr as the RTOS to operate the system. To create and train the AI model and deploy it to the Arduino Nano microcontroller, I used Edge Impulse. I also used it to edit some audio data to fit within the 1-second window for training the model.

I used the Pete Warden voice dataset as the AI databse. The files used in this project can be accessed [here](https://drive.google.com/file/d/17HAxpKHDkPuj7wIeOMZ8yrCH6MHIF1b3/view?usp=sharing).

## Getting Started

Follow these instructions to set up and run the EchoCar project.

### Prerequisites

The project is divided into firmware and hardware.

For the hardware, check the project BOM for the required components.

```
STM32F103C8T6 microcontroller  
Arduino Nano 33 BLE Sense  
EchoCar's PCB  
2x 18650 batteries  
BOM components  
```

For the firmware, install the Zephyr RTOS and the Arduino IDE. You can follow the instructions on the Zephyr Getting Started page to install it on your machine and download the Arduino IDE from their website.

### Installing

After installing Zephyr, flash the firmware onto the STM32F103 using a flasher device such as the ST-Link v2.

First, build the project using:

```
west build -p
```

Then, flash it using:

```
west flash
```

For the Arduino firmware, install the EchoCar_inferencing.rar library in the Arduino IDE, then flash the .ino file to the Arduino Nano microcontroller.

## Built With

* [Zephyr RTOS](https://www.zephyrproject.org/) - The RTOS used.  
* [Edge Impulse](https://edgeimpulse.com/) - Used for AI model development.  
* [KiCad](https://www.kicad.org/) - Used to design the PCB.
* [Pete Warden Dataset](https://arxiv.org/pdf/1804.03209) - AI Dataset.

## Author

* **Victor Hugo Sampaio**

## Video
YouTube [link](https://youtu.be/iiWRqvPNBO4).


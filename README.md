# [STM32F401]-[UART-TX-RX]-[Register] Example.

##  🎯 Overview.

This repository contains a complete, self-contained coding example demonstrating the configuration and usage of the [UART] peripheral on the [Nucleo F401RE Board - STM32F401RE].

### 💡 Objective

The primary goal of this exercise is to implement a simple bare-metal uart application to send and receive message through terminal serial and toggle a LED of Nucleo-F401RE. The change of state of the GPIO was build with directly register accesing.

### ⚙️ Hardware & Software Details.
| Component  | Value | Notes |
| ------------- | ------------- | ------------- |
| Microcontroller  | STM32F401RE  | ARM Cortex M4  |
| Development Board  | Nucleo F401RE  | Specific hardware used for testing  |
| Peripheral Used | UART Peripheral, GPIO Port A, HSI | Led, Teraterm High-Speed Internal Clock |
| Clock Configuration | Internal Clock (16MHz), System Clock (84MHz) |

### Toolchain Used

This project was developed and tested using the following specific toolchain:

IDE: Keil uVision v5.42

Compiler: ArmClang v6.23

Debugger: ST-Link v2

### 🛠️ Implementation Details (The Code)

1. Register Abstraction Level: This project uses Direct Register Access

2. Key Configuration Steps

- Clock Enable: The clock for the GPIO Port A and for UART2 was enabled via the RCC AHBxENR register and APBxENR register.

- Pin Mode: Pin PA5 was set to Output Mode by writing to the GPIOx_MODER register. Also, set Pin PA2 and PA3 to alternate function mode

3. Execution Flow

- The main() function enable the clock for GPIO, initializes the UART peripheral and then enters an infinite loop, where it checks for the data receive, if it receives "1" turns the LED on else turns the LED off.

### ➡️ Build and Run Instructions

1. Clone this specific repository:

> git clone git@github.com:cart1993/STM32F401-GPIO-Register.git

2. Open the project file .uvprojx in keil uVision 5.

3. Build the project.

4. Flash the resulting .elf or .hex file to the target board using the STLink V2

### 📄 License

This exercise is part of the main Baremetal : ARM Cortex-M Embedded Coding Exercises project and is released under the MIT License.

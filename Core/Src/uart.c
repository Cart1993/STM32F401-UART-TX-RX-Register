#include "uart.h"

#define GPIOAEN		(1U<<0)
#define USART2EN	(1U<<17)

#define CR1_TE		(1U<<3)
#define CR1_UE		(1U<<13)
#define CR1_RE		(1U<<2)

#define SR_TXE		(1U<<7)
#define SR_RXNE		(1U<<5)

#define SYS_FREQ	16000000 //Default system frequency, if we've not configured the clock tree
#define APB1_CLK	SYS_FREQ //Because we've not configured the clock tree (divider 1)

#define UART_BAUDRATE	115200

static void usart_set_baudRate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate);
static uint16_t compute_usart_bd(uint32_t periphClk, uint32_t baudRate);

void usart2_write(int ch);

int __io_putchar(int ch)
{
	usart2_write(ch);
	return ch;
}

void usart2_rxtx_init(void)
{
	/*********Configure uart gpio pin*********/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= (1U<<0);
	/*Set PA2 and PA3 to alternate function mode*/
	GPIOA->MODER &=~(1U<<4)|(1U<<6);
	GPIOA->MODER |= (1U<<5)|(1U<<7);
	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8)|(1U<<9)|(1U<<10)|(1U<<12)|(1U<<13)|(1U<<14);
	GPIOA->AFR[0] &=~(1U<<11)|(1U<<15);

	/*********Configure uart module************/
	/*Enable clock access to uart2*/
	RCC->APB1ENR |= (1U<<17);
	/*Configure baudrate*/
	usart_set_baudRate(USART2, APB1_CLK, UART_BAUDRATE);
	/*Configure the transfer direction*/
	USART2->CR1 = CR1_TE;
	/*Configure the enable receiver*/
	USART2->CR1 = CR1_RE;
	/*Enable UART module*/
	USART2->CR1 |= CR1_UE;
}

char usart2_read(void)
{
	/*Make sure the receive data register is not empty*/
	while(!(USART2->SR & SR_RXNE)){}
	return USART2->DR;
}

void usart2_write(int ch)
{
	/*Make sure the transmit data register is empty*/
	while(!(USART2->SR & SR_TXE)){}
	/*Write to transmit to data register*/
	USART2->DR = (ch & 0xFF);
}

static void usart_set_baudRate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate)
{
	USARTx->BRR |= compute_usart_bd(periphClk, baudRate);
}

static uint16_t compute_usart_bd(uint32_t periphClk, uint32_t baudRate)
{
	return ((periphClk+(baudRate/2U))/baudRate);
}

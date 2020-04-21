#include <timer.h>
#include "uart.h"

interface uart_interface = {
		.is_new_frame_availible = FALSE,
		.current_frame_size = 0
};

interface* get_uart_interface_status(void){
	return &uart_interface;
}

boolean is_new_frame_availible(void){
	return uart_interface.is_new_frame_availible;
}

void init_uart(uint16_t baudrate) {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOB,
			ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_7;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;

	USART_InitTypeDef uart;
	USART_StructInit(&uart);
	uart.USART_BaudRate = baudrate;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_WordLength = USART_WordLength_8b;

	USART_Init(UART_K, &uart);
	USART_ITConfig(UART_K, USART_IT_RXNE, ENABLE);

	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	USART_ClearFlag(USART1, USART_IT_TXE);
	USART_Cmd(UART_K, ENABLE);
}

void send_char(char c) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		USART_SendData(USART1, c);
}

void transmit_data(const char* data) {
	while (*data)
		send_char(*data++);
}

void USART1_IRQHandler() {
	if (USART_GetFlagStatus(UART_K, USART_IT_RXNE) == SET) {
		USART_ClearITPendingBit(UART_K, USART_IT_RXNE);
		uint8_t rx_value = USART_ReceiveData(UART_K);
		switch (rx_value) {
		case FRAME_INIT_CHAR:
			uart_interface.current_frame_size = 0;
			break;
		case FRAME_END_CHAR:
			uart_interface.is_new_frame_availible = TRUE;;
			break;
		default:
			uart_interface.rx_data[uart_interface.current_frame_size] = rx_value;
			uart_interface.current_frame_size++;
			break;
		}
	}
}

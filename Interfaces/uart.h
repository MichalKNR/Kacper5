
#ifndef UART_H_
#define UART_H_

#define UART_K USART1
#include <stddef.h>
#include "stm32f10x.h"
#include "typedefs.h"

#define FRAME_INIT_CHAR 's'
#define FRAME_END_CHAR 'e'
#define FRAME_DATA_LENGHT 4

#define MAX_RX_DATA 10
#define MAX_TX_DATA 10

typedef struct {
	uint8_t rx_data[MAX_RX_DATA];
	boolean is_new_frame_availible;
	uint8_t current_frame_size;
}interface;

void init_uart(uint16_t baudrate);

void transmit_data(const char* data);

void send_char(char c);

interface* get_uart_interface_status(void);

boolean is_new_frame_availible(void);

#endif /* UART_H_ */

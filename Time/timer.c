/*
 * misc.c
 *
 *  Created on: 18.11.2018
 *      Author: micha
 */

#include <timer.h>

void delay_ms(uint32_t time_ms) {
	Delay_Time_ms = time_ms;
	while (Delay_Time_ms != 0) {
	}
}
void decrement_time_delay() {
	if (Delay_Time_ms != 0)
		Delay_Time_ms--;
}


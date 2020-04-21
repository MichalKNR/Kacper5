/*
 * misc.h
 *
 *  Created on: 18.11.2018
 *      Author: Joanna
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>
void delay_ms(uint32_t time_ms);

//use in system systick
void decrement_time_delay();

uint32_t Delay_Time_ms;
int kupa;

#endif /* TIMER_H_ */

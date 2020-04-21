/*
 * system_init.h
 *
 *  Created on: 06.04.2020
 *      Author: micha
 */

#ifndef SYSTEM_INIT_H_
#define SYSTEM_INIT_H_


#include "stm32f10x.h"

static inline void initialize_system(void){
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);

	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOB, &gpio);
}


#endif /* SYSTEM_INIT_H_ */

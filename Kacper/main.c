/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <timer.h>
#include "uart.h"
#include "motor.h"
#include "system_init.h"
#include "typedefs.h"

int main(void) {

	initialize_system();

	GPIO_SetBits(GPIOB, GPIO_Pin_10);

	init_uart(9600);

	while (1) {
		delay_ms(1);
		if(is_new_frame_availible()){
			motor_control();
		}
		if(motors_watchdog_timer.is_counter_active){
        	motors_watchdog_timer.counter++;
        	if(motors_watchdog_timer.counter >= DEFAULT_WATCHDOG_TIMER_DELAY){
        		motors_watchdog_timer.is_counter_active = FALSE;
        		STOP();
        	}
		}
	}
}

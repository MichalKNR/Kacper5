
#ifndef MOTOR_H_
#define MOTOR_H_

#include <stddef.h>
#include "stm32f10x.h"
#include  "motor.h"
#include "uart.h"
#include "typedefs.h"

#define M_LEFT 1
#define M_RIGHT 2

#define MOTORS_START_MSG_INDEX   0
#define MOTORS_LEFT_SPEED_INDEX  1
#define MOTORS_RIGHT_SPEED_INDEX 2

#define PWM_MAX_VALUE 255
#define DEFAULT_WATCHDOG_TIMER_DELAY 100

typedef struct{
	uint8_t counter;
	boolean is_counter_active;
}watchdog_timer;

watchdog_timer motors_watchdog_timer;

void init_Encoders();

void change_Speed(int speed_left, int speed_right); // (-999) - 999

void update_control_logic(void);

void STOP();

void motor_control(void);



#endif /* MOTOR_H_ */

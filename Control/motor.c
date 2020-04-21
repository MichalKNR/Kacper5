#include "motor.h"

int active_speed_left = 0;
int active_speed_right = 0;

extern watchdog_timer motors_watchdog_timer;

#define DEFAULT_CONTROL_MODE_DATA_INDEX 0

typedef enum {
	stop = 0,
	forward,
	backward,
	right,
	left
}differential_drive_mode;

typedef struct{
	boolean is_active;
	differential_drive_mode drive_mode;
}control_logic;

void change_Speed(int speed_left, int speed_right) {
	if (speed_left >= 0) {
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		TIM_SetCompare1(TIM2, speed_left);
		active_speed_left = speed_left;
	} else {
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		TIM_SetCompare1(TIM2, PWM_MAX_VALUE);
		active_speed_left = -speed_left;
	}

	if (speed_right >= 0) {
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		TIM_SetCompare2(TIM2, PWM_MAX_VALUE);
		active_speed_right = speed_right;
	} else {
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		TIM_SetCompare2(TIM2, PWM_MAX_VALUE);
		active_speed_right = speed_right;
	}
}

void motor_left_forward(){
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	TIM_SetCompare1(TIM2, PWM_MAX_VALUE);
}

void motor_right_forward(){
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	TIM_SetCompare2(TIM2, PWM_MAX_VALUE);
}

void motor_left_backward(){
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	TIM_SetCompare1(TIM2, PWM_MAX_VALUE);
}

void motor_right_backward(){
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	TIM_SetCompare2(TIM2, PWM_MAX_VALUE);
}

void left_motor_stop(){
	TIM_SetCompare1(TIM2, 0);
}

void right_motor_stop(){
	TIM_SetCompare2(TIM2, 0);
}

void go_forward(){
	motor_left_forward();
	motor_right_forward();
}

void go_backward(){
	motor_left_backward();
	motor_right_backward();
}

void turn_left(){
	motor_right_forward();
	motor_left_backward();
}

void turn_right(){
	motor_left_forward();
	motor_right_backward();
}

void STOP(){
	left_motor_stop();
	right_motor_stop();
}

void set_watchdog_active(){
	motors_watchdog_timer.counter = 0;
	motors_watchdog_timer.is_counter_active = TRUE;
}

void motor_control(void) {
	switch (get_uart_interface_status()->rx_data[DEFAULT_CONTROL_MODE_DATA_INDEX]) {
	case 'w':
		set_watchdog_active();
		go_forward();
		break;
	case 's':
		set_watchdog_active();
		go_backward();
		break;
	case 'a':
		set_watchdog_active();
		turn_left();
		break;
	case 'd':
		set_watchdog_active();
		turn_right();
		break;
	default:
		STOP();
		break;
	}
}


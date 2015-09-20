#include "../Devices/servodrive.h"

#include <avr/io.h>

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)

volatile int pwm_width;
volatile int servo_position;
volatile int servo_position_aux;

const int DEG_LEFT = 2;
const int DEG_CENTER = 3;
const int DEG_RIGHT = 4;

const int MS_20 = 40;
const int MS_200 = 400;

void init_servodrive() {
	pwm_width = DEG_CENTER;
	servo_position = 0;
	servo_position_aux = 0;
}

void turn_to_position(int position) {
	if(servo_position != position) {
		pwm_width = position;
	}
}

void turn_servodrive_left() {
	turn_to_position(DEG_LEFT);
}

void turn_servodrive_right() {
	turn_to_position(DEG_RIGHT);
}

void center_servodrive() {
	turn_to_position(DEG_CENTER);
}

void handle_tracking(long counter) {
	if(counter % MS_200 == 0) {
		if(servo_position_aux != servo_position) {
			pwm_width = 0;
			servo_position = servo_position_aux;
			return;
		}
		servo_position_aux = pwm_width;
	}
}

void handle_movement(long counter) {
	if(counter % MS_20 < pwm_width) {
		sbi(PORTA, 7);
	} else {
		cbi(PORTA, 7);
	}
}

void handle_servodrive(long counter) {
	handle_tracking(counter);
	handle_movement(counter);
}

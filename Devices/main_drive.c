#include "../Devices/step_motor.h"

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

volatile int full_mode;
volatile int direction;
volatile int speed;

unsigned int internal_counter;

const char FULL_MOVEMENT[] = { 0x0A, 0x06, 0x05, 0x09 };
const char HALF_MOVEMENT[] = { 0x08, 0x02, 0x04, 0x01 };

const long MIN_1 = 120000;
const int PERIOD = 4;

void init_step_motor() {
	full_mode = 1;
	direction = 1;
	speed = 0;
	internal_counter = 0;
}

void run(int mode, int dir, int sp) {
	full_mode = mode;
	direction = dir;
	speed = sp;
}

void run_forward_full_mode(int sp) {
	run(1, 1, sp);
}

void run_forward_half_mode(int sp) {
	run(0, 1, sp);
}

void run_backward_full_mode(int sp) {
	run(1, -1, sp);
}

void run_backward_half_mode(int sp) {
	run(0, -1, sp);
}

void stop() {
	speed = 0;
}

void handle_motor_movement() {
	if (full_mode) {
		PORTA = FULL_MOVEMENT[internal_counter % PERIOD];
	} else {
		PORTA = HALF_MOVEMENT[internal_counter % PERIOD];
	}
}

void handle_step_motor(long counter) {
	if (speed != 0 && counter % (MIN_1 / (speed * PERIOD)) == 0) {
		handle_motor_movement();
		internal_counter += direction;
	}
}

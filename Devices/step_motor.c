#include "../Devices/step_motor.h"

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

volatile int full_mode;
volatile int direction;
volatile int speed;

volatile unsigned int distance_counter;
volatile int distance_setpoint;
volatile int distance_mode;

volatile unsigned int step_counter;
volatile int step_point;

const char FULL_STEPS[] = { 0x0A, 0x06, 0x05, 0x09 };
const char HALF_STEPS[] = { 0x08, 0x02, 0x04, 0x01 };

const long MIN_1 = 120000;
const int PERIOD = 4;

void init_step_motor() {
	full_mode = 1;
	direction = 1;
	speed = 0;
	step_counter = 0;
	step_point = 0;
}

void stop() {
	speed = 0;
}

void run(int mode, int dir, int sp) {
	full_mode = mode;
	direction = dir;
	speed = sp;
	step_point = MIN_1 / (speed * PERIOD);
}

int run_distance(int mode, int dir, int sp, int dist, int dist_mode) {
	run(mode, dir, sp);
	if (dist_mode != distance_mode) {
		distance_counter = 0;
		distance_mode = dist_mode;
		distance_setpoint = dist;
	}
	if (distance_counter >= dist) {
		distance_setpoint = 0;
		distance_mode = 0;
		return 1;
	}
	return 0;
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

int run_forward_full_mode_distance(int sp, int dist) {
	return run_distance(1, 1, sp, dist, 1);
}

int run_forward_half_mode_distance(int sp, int dist) {
	return run_distance(0, 1, sp, dist, 1);
}

int run_backward_full_mode_distance(int sp, int dist) {
	return run_distance(1, -1, sp, dist, -1);
}

int run_backward_half_mode_distance(int sp, int dist) {
	return run_distance(0, -1, sp, dist, -1);
}

void handle_motor_movement() {
	if (full_mode) {
		PORTA = FULL_STEPS[step_counter % PERIOD];
	} else {
		PORTA = HALF_STEPS[step_counter % PERIOD];
	}
}

void handle_step_motor(int counter) {
	if (speed != 0 && counter % step_point == 0) {
		handle_motor_movement();
		step_counter += direction;
		if (distance_counter++ >= distance_setpoint && distance_setpoint != 0) {
			stop();
		}
	}
}

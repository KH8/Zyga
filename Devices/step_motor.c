#include "step_motor.h"

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

volatile unsigned int full_mode;
volatile int direction;
volatile unsigned long speed;

const char FULL_STEPS[] = { 0x0A, 0x06, 0x05, 0x09 };
const char HALF_STEPS[] = { 0x08, 0x02, 0x04, 0x01 };

unsigned long step_counter;
char steps[4];

const unsigned long MIN_1 = 120000;
const unsigned long PERIOD = 4;

void init_step_motor() {
	full_mode = 1;
	direction = 1;
	speed = 0;
	step_counter = 0;
}

void run(unsigned int mode, int dir, unsigned long sp) {
	full_mode = mode;
	direction = dir;
	speed = sp;

	if (full_mode) {
		strcpy(steps, FULL_STEPS);
	} else {
		strcpy(steps, HALF_STEPS);
	}
}

void run_forward_full_mode(unsigned long sp) {
	run(1, 1, sp);
}

void run_forward_half_mode(unsigned long sp) {
	run(0, 1, sp);
}

void run_backward_full_mode(unsigned long sp) {
	run(1, -1, sp);
}

void run_backward_half_mode(unsigned long sp) {
	run(0, -1, sp);
}

void stop() {
	speed = 0;
}

void handle_step_motor(unsigned long counter) {
	if (speed != 0 && counter % (MIN_1 / (speed * PERIOD)) == 0) {
		PORTA = steps[step_counter % PERIOD];
		step_counter += direction;
	}
}

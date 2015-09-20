#include "../Devices/main_drive.h"

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

volatile int full_mode;
volatile int direction;
volatile int speed;

const char FULL_MOVEMENT[] = {0x0A, 0x06, 0x05, 0x09};
const char HALF_MOVEMENT[] = {0x08, 0x02, 0x04, 0x01};

unsigned long internal_counter;
char movement[4];

const long MIN_1 = 120000;
const long PERIOD = 4;

void init_main_drive() {
	full_mode = 1;
	direction = 1;
	speed = 0;
	internal_counter = 0;
}

void run(int mode, int dir, long sp) {
	full_mode = mode;
	direction = dir;
	speed = sp;

	if(full_mode) {
		strcpy(movement, FULL_MOVEMENT);
	} else {
		strcpy(movement, HALF_MOVEMENT);
	}
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

void handle_main_drive(long counter) {
	if(speed != 0 && counter % (MIN_1 / (speed * PERIOD)) == 0) {
		PORTA = movement[internal_counter % PERIOD];
		internal_counter += direction;
	}
}

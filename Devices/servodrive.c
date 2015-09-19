#include "../Devices/servodrive.h"

#include <avr/io.h>

#include "buzzer.h"

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)

volatile double pwm_width;

volatile int counter;

const int DEG_0 = 10;
const int DEG_90 = 50;
const int DEG_180 = 20;

const double MAX_COUNTER = 200;

void init_servodrive() {
	pwm_width = DEG_90;
	counter = 0;
}

void turn_servodrive_left() {
	pwm_width = DEG_0;
}

void turn_servodrive_right() {
	pwm_width = DEG_180;
}

void center_servodrive() {
	pwm_width = DEG_90;
}

void handle_servodrive() {
	if(counter < pwm_width) {
		sbi(PORTA, 7);
	} else {
		cbi(PORTA, 7);
	}
	counter++;
	if(counter > MAX_COUNTER) {
		counter = 0;
	}
}

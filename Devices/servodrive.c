#include "../Devices/servodrive.h"

#include <avr/io.h>

#include "buzzer.h"

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)

volatile double pwm_width;

volatile int counter;
volatile int counter_max;

const int DEG_0 = 12;
const int DEG_90 = 20;
const int DEG_180 = 28;

const double PERIOD = 200;

void init_servodrive() {
	pwm_width = DEG_90;
	counter = 0;
	counter_max = PERIOD;
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
	if(counter > counter_max) {
		counter = 0;
	}
}

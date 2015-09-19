#include "../Devices/servodrive.h"

#include <avr/io.h>

#include "buzzer.h"

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)

volatile int pwm_width;

const int DEG_0 = 10;
const int DEG_90 = 2;
const int DEG_180 = 20;

const int MS_20 = 40;

void init_servodrive() {
	pwm_width = DEG_90;
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

void handle_servodrive(long counter) {
	if(counter % MS_20 < pwm_width) {
		sbi(PORTA, 7);
	} else {
		cbi(PORTA, 7);
	}
}

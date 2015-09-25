#include "../Devices/proxi_switch.h"

#include <avr/io.h>

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

volatile int front_up = 0;
volatile int front_down = 0;
volatile int left_up = 0;
volatile int right_up = 0;

const int FILTER_SIZE = 10;

void init_proxi_switch() {
	front_up = 0;
	front_down = 0;
	left_up = 0;
	right_up = 0;
}

int proxi_switch_front_up() {
	return bit_is_clear(PIND, 2);
}

int proxi_switch_front_down() {
	return bit_is_clear(PIND, 4);
}

int proxi_switch_left_up() {
	return bit_is_clear(PIND, 6);
}

int proxi_switch_right_up() {
	return bit_is_clear(PINA, 5);
}

int proxi_switch_front_up_filtered() {
	return front_up > 0;
}

int proxi_switch_front_down_filtered() {
	return front_down > 0;
}

int proxi_switch_left_up_filtered() {
	return left_up > 0;
}

int proxi_switch_right_up_filtered() {
	return right_up > 0;
}

void handle_proxi_switch() {
	PORTD ^= (0xA8 << 0);
	PORTA ^= (0x40 << 0);
}

void handle_proxi_switch_filter(int counter) {
	if(proxi_switch_front_up()) {
		front_up = FILTER_SIZE;
	} else {
		front_up--;
	}
	if(proxi_switch_front_down()) {
		front_down = FILTER_SIZE;
	} else {
		front_down--;
	}
	if(proxi_switch_left_up()) {
		left_up = FILTER_SIZE;
	} else {
		left_up--;
	}
	if(proxi_switch_right_up()) {
		right_up = FILTER_SIZE;
	} else {
		right_up--;
	}
}

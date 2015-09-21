#include "../Devices/proxi_switch.h"

#include <avr/io.h>

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

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

void handle_proxi_switch() {
	PORTD ^= (0xA8 << 0);
	PORTA ^= (0x40 << 0);
}

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Devices/servodrive.h"
#include "Auxiliaries/delay.h"

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

ISR(TIMER1_COMPA_vect) {
	handle_delays();
	//handle_servodrive();
}

ISR(TIMER2_COMP_vect) {
}

int main(void) {
	configure_ports();
	configure_timers();

	init_delays();
	init_servodrive();

	sei();

	while (1) {
		if (bit_is_clear(PIND, 0)) {
			tbi(PORTC, 7);
			delay_s(1);
		}
	}
}

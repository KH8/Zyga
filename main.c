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

volatile long counter_b;
volatile long counter_b_max;

ISR(TIMER1_COMPA_vect) {
	handle_servodrive();
}

ISR(TIMER2_COMP_vect) {
	counter_b++;
	if(counter_b > counter_b_max) {
		counter_b = 0;
	}
}

int main(void) {
	configure_ports();
	configure_timers();

	counter_b = 0;
	counter_b_max = 20000;

	init_servodrive();

	sei();

	while (1) {
		if (bit_is_clear(PIND, 0)) {
			turn_servodrive_left();

			_delay_ms(20);
			center_servodrive();

			_delay_ms(20);
			turn_servodrive_right();

			_delay_ms(20);
			center_servodrive();

			_delay_ms(20);
		}
	}
}

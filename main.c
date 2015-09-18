#include <avr/io.h>
#include <avr/interrupt.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Auxiliaries/delay.h"

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

volatile long counter;
volatile long counter_max;

ISR(TIMER1_COMPA_vect) {
	counter++;
	if(counter > counter_max) {
		counter = 0;
	}
}

int main(void) {
	configure_ports();
	configure_timers();

	counter = 0;
	counter_max = 720;

	sei();

	while (1) {
		if (bit_is_clear(PIND, 0)) {
			buzzer(440, 1);
			delay_s(1);
			buzzer(880, 1);
			delay_s(1);
		}
	}
}

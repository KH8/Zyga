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

volatile long counter_a;
volatile long counter_a_max;
volatile long counter_b;
volatile long counter_b_max;

ISR(TIMER1_COMPA_vect) {
	counter_a++;
	if(counter_a > counter_a_max) {
		counter_a = 0;
		//buzzer(2, 1);
	}
}

ISR(TIMER2_COMP_vect) {
	counter_b++;
	if(counter_b > counter_b_max) {
		counter_b = 0;
		buzzer(2, 1);
	}
}

int main(void) {
	configure_ports();
	configure_timers();

	counter_a = 0;
	counter_a_max = 20000;
	counter_b = 0;
	counter_b_max = 20000;

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

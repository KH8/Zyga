#include <avr/io.h>
#include <avr/interrupt.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Devices/dip_switch.h"
#include "Devices/servodrive.h"
#include "Auxiliaries/delay.h"

volatile long counter;

ISR(TIMER1_COMPA_vect) {
	handle_servodrive(counter);
	handle_delays(counter);
	counter++;
}

ISR(TIMER2_COMP_vect) {
}

int main(void) {
	configure_ports();
	configure_timers();

	counter = 0;
	init_delays();
	init_servodrive();

	sei();

	while (1) {
		if (switch_2()) {
			buzzer(10, 100);
			delay_s(1);
		}
	}
}

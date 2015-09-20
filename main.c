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
			buzzer(200, 100);
			/*turn_servodrive_left();
			delay_s(5);
			center_servodrive();*/
			delay_s(5);
		}
		if (switch_3()) {
			buzzer(100, 100);
			turn_servodrive_right();
			delay_s(5);
			center_servodrive();
			delay_s(5);
		}
	}
}

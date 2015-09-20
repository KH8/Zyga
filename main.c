#include <avr/io.h>
#include <avr/interrupt.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Devices/dip_switch.h"
#include "Devices/servodrive.h"
#include "Devices/main_drive.h"
#include "Devices/proxi_switch.h"
#include "Auxiliaries/delay.h"

volatile long counter;

ISR(TIMER1_COMPA_vect) {
	handle_main_drive(counter);
	//handle_servodrive(counter);
	handle_delays(counter);
	counter++;
}

ISR(TIMER2_COMP_vect) {
	handle_proxi_switch();
}

int main(void) {
	configure_ports();
	configure_timers();

	counter = 0;
	init_main_drive();
	init_servodrive();
	init_delays();

	sei();

	while (1) {
		if (proxi_switch_front_up()) {
			buzzer(100, 10);
		}
		delay_ms(5);
	}
}

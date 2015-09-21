#include <avr/io.h>
#include <avr/interrupt.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Devices/dip_switch.h"
#include "Devices/servodrive.h"
#include "Devices/step_motor.h"
#include "Devices/proxi_switch.h"
#include "Auxiliaries/delay.h"

volatile unsigned long counter;

ISR(TIMER1_COMPA_vect) {
	handle_step_motor(counter);
	handle_servodrive(counter);
	handle_delays(counter);
	counter++;
}

ISR(TIMER2_COMP_vect) {
	//handle_proxi_switch();
}

int main(void) {
	configure_ports();
	configure_timers();

	counter = 0;
	init_step_motor();
	init_servodrive();
	init_delays();

	sei();

	//run_forward_half_mode(30000);

	while (1) {
		buzzer(220, 100);
		delay_s(2);
	}
}

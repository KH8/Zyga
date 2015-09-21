#include <avr/io.h>
#include <avr/interrupt.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Devices/dip_switch.h"
#include "Devices/servodrive.h"
#include "Devices/step_motor.h"
#include "Devices/proxi_switch.h"
#include "Auxiliaries/delay.h"

volatile long counter;

ISR(TIMER1_COMPA_vect) {
	handle_step_motor(counter);
	handle_servodrive(counter);
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
	init_step_motor();
	init_servodrive();
	init_delays();

	sei();

	while (1) {
		while (1) {
			if (switch_2()) {
				buzzer(200, 100);
				run_forward_full_mode(30000);
				delay_s(5);
				stop();
				delay_s(5);
				run_backward_full_mode(30000);
				delay_s(5);
				stop();
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
}

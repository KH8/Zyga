#include <avr/io.h>
#include <avr/interrupt.h>

#include "Configuration/configuration.h"
#include "Devices/buzzer.h"
#include "Devices/dip_switch.h"
#include "Devices/servodrive.h"
#include "Devices/step_motor.h"
#include "Devices/proxi_switch.h"
#include "Auxiliaries/delay.h"

volatile long counter_a;
volatile long counter_b;

int INIT_TIME = 3;

void handle_2kHz_interrupt() {
	handle_step_motor(counter_b);
	handle_servodrive(counter_b);
	counter_b++;
}

void handle_64kHz_interrupt() {
	handle_proxi_switch();
	handle_delays(counter_a);
	if(counter_a % 32 == 0) {
		handle_2kHz_interrupt();
	}
	counter_a++;
}

ISR(TIMER1_COMPA_vect) {
	handle_64kHz_interrupt();
}

int main(void) {
	configure_ports();
	configure_timers();

	counter_a = 0;
	counter_b = 0;
	init_step_motor();
	init_servodrive();
	init_delays();

	sei();

	while(INIT_TIME--) {
		buzzer(220, 100);
		delay_s(1);
	}

	while (1) {
		if (proxi_switch_front_up()) {
			buzzer(200, 100);
		}
		if (proxi_switch_front_down()) {
			buzzer(200, 100);
		}
		if (proxi_switch_right_up()) {
			buzzer(200, 100);
		}
		if (proxi_switch_left_up()) {
			buzzer(200, 100);
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

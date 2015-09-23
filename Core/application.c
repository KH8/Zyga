#include "../Core/application.h"

#include <avr/interrupt.h>

#include "../Configuration/configuration.h"

#include "../Devices/step_motor.h"
#include "../Devices/servodrive.h"
#include "../Devices/proxi_switch.h"
#include "../Devices/dip_switch.h"
#include "../Devices/buzzer.h"

#include "../Auxiliaries/delay.h"

#include "../Modes/mode_0.h"
#include "../Modes/mode_1.h"
#include "../Modes/mode_2.h"
#include "../Modes/mode_3.h"

volatile unsigned int counter_a;
volatile unsigned int counter_b;

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

void interrupt_loop() {
	handle_64kHz_interrupt();

}

void initialize() {
	counter_a = 0;
	counter_b = 0;

	configure_ports();
	configure_timers();

	init_step_motor();
	init_servodrive();
	init_delays();

	sei();

	while(INIT_TIME--) {
		buzzer(440, 100);
		delay_s(1);
	}
}

int get_mode() {
	return switch_2() + ( 2* switch_3() );
}

void pre_loop() {
	//
}

void post_loop() {
	//
}

void main_loop() {
	pre_loop();
	switch(get_mode()) {
		case 0:
			handle_mode_0();
		break;
		case 1:
			handle_mode_1();
		break;
		case 2:
			handle_mode_2();
		break;
		case 3:
			handle_mode_3();
		break;
	}
	post_loop();
}

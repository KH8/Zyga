#include <avr/interrupt.h>

#include "Core/application.h"

ISR(TIMER1_COMPA_vect) {
	interrupt_loop();
}

int main(void) {
	initialize();
	while (1) {
		main_loop();
	}
}

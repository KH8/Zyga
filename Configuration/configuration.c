#include "../Configuration/configuration.h"

#include <avr/io.h>

const int FREQ__36_KHZ = 115;

void configure_ports() {
	DDRA = 0xCF;
	PORTA = 0xF0;
	DDRC = 0xFF;
	PORTC = 0xFF;
	DDRD = 0xAB;
	PORTD = 0xFF;
	DDRB = 0x00;
	PORTB = 0xFF;
}

void configure_timers() {
	TCCR1B = (1 << WGM12) | (1 << CS10);
	OCR1A = FREQ__36_KHZ;
	TIMSK = (1 << OCIE1A);
}


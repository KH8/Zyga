#include "../Configuration/configuration.h"

#include <avr/io.h>

const int FREQ_2_KHZ = 4499;
const int FREQ_36_KHZ = 115;

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
	OCR1A = FREQ_2_KHZ;
	TCCR2 = (1 << WGM21) | (1 << CS20);
	OCR2 = FREQ_36_KHZ;
	TIMSK = (1 << OCIE1A) | (1 << OCIE2);
}


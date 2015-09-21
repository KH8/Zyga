#include "../Devices/buzzer.h"

#include <avr/io.h>

#include "../Auxiliaries/delay.h"

#define tbi(port, pin) (port) ^= _BV(pin)

long SECOND_MS = 1000;

void buzzer(int frequency, int length) {
	long interval = SECOND_MS / ( 2 * frequency );
	long count = length / interval;
	while (count--) {
		tbi(PORTC, 7);
		delay_ms(interval);
	}
}

#include "../Devices/buzzer.h"

#include <avr/io.h>

#include "../Auxiliaries/delay.h"

#define tbi(port, pin) (port) ^= _BV(pin)

long SECOND_US = 1000;

void buzzer(int frequency, int length) {
	long interval = SECOND_US / ( 2 * frequency );
	long count = length * frequency / 2;
	while (count--) {
		tbi(PORTC, 7);
		delay_ms(interval);
	}
}

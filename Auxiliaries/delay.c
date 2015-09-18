#include "../Auxiliaries/delay.h"

#include <util/delay.h>

void delay_s(int s) {
	while(s--) {
		_delay_ms(1000.0);
	}
}

void delay_ms(int ms) {
	while(ms--) {
		_delay_ms(1.0);
	}
}

void delay_us(int us) {
	while(us--) {
		_delay_us(1.0);
	}
}

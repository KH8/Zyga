#include "../Auxiliaries/delay.h"

volatile unsigned long counter_s;
volatile unsigned long counter_ms;

const unsigned int MS_1 = 2;

void init_delays() {
	counter_s = 0;
	counter_ms = 0;
}

void delay_s(int s) {
	long time_to_stop = counter_s + s;
	while (time_to_stop > counter_s) {
		//wait
	}
}

void delay_ms(int ms) {
	long time_to_stop = counter_ms + ms;
	while (time_to_stop > counter_ms) {
		//wait
	}
}

void handle_delays(unsigned long counter) {
	if (counter % MS_1 == 0) {
		counter_ms++;
		counter_s = counter_ms / 1000;
	}
}

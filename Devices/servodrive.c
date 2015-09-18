#include "../Devices/servodrive.h"

#include <avr/io.h>
#include <util/delay.h>

int time_recquired = 50;
int servo_position = 0;

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)

void turn_left() {
	int t = time_recquired;
	while(t--)
	{
		sbi(PORTA, 7);
		_delay_ms(1);
		cbi(PORTA, 7);
		_delay_ms(19);
	}
}

void turn_right() {
	int t = time_recquired;
	while(t--)
	{
		sbi(PORTA, 7);
		_delay_ms(2);
		cbi(PORTA, 7);
		_delay_ms(18);
	}
}

void center() {
	int t = time_recquired;
	while(t--)
	{
		sbi(PORTA, 7);
		_delay_ms(1.5);
		cbi(PORTA, 7);
		_delay_ms(18.5);
	}
}

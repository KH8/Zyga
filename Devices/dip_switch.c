#include "../Devices/dip_switch.h"

#include <avr/io.h>

#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

int switch_2() {
	return bit_is_clear(PIND, 0);
}

int switch_3() {
	return bit_is_clear(PIND, 1);
}

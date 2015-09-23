#include "../Modes/mode_2.h"

#include "../Devices/buzzer.h"
#include "../Auxiliaries/delay.h"

void handle_mode_2() {
	buzzer(440, 100);
	delay_s(2);
}

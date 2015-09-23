#include "../Modes/mode_1.h"

#include "../Devices/buzzer.h"
#include "../Auxiliaries/delay.h"

void handle_mode_1() {
	buzzer(440, 100);
	delay_s(1);
}

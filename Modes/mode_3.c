#include "../Modes/mode_3.h"

#include "../Devices/buzzer.h"
#include "../Auxiliaries/delay.h"

void handle_mode_3() {
	buzzer(220, 100);
	delay_s(2);
}

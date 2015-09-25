#include "../Modes/mode_2.h"

#include "../Devices/proxi_switch.h"
#include "../Devices/buzzer.h"
#include "../Auxiliaries/delay.h"

int get_sensor_states() {
	return proxi_switch_front_up()
			+ (2 * proxi_switch_front_down())
			+ (4 * proxi_switch_left_up())
			+ (8 * proxi_switch_right_up());
}

void handle_mode_2() {
	if(get_sensor_states() != 0) {
		buzzer(220, 10);
	}
}

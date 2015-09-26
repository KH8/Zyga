#include "../Modes/mode_0.h"

#include "../Devices/step_motor.h"
#include "../Devices/servodrive.h"

void handle_mode_0() {
	stop();
	center_servodrive();
}

#include "../Modes/mode_1.h"

#include "../Devices/step_motor.h"
#include "../Devices/servodrive.h"
#include "../Devices/proxi_switch.h"
#include "../Devices/buzzer.h"
#include "../Auxiliaries/delay.h"

int manover_mode = 0;
int manover_execution = 0;

int FULL_SPEED = 30000;
int MID_SPEED = 20000;
int SLOW_SPEED = 5000;

int FULL_TURN_DIST = 2000;
int HALF_TURN_DIST = 1000;
int GO_BACKWARD_DIST = 1000;

int get_side_sensors_status() {
	return proxi_switch_left_up() + (2*proxi_switch_right_up());
}

void compute_mode() {
	if (manover_execution) {
		return;
	}
	if (!proxi_switch_front_down()) {
		manover_mode = 0;
		return;
	}
	if (!proxi_switch_front_up()) {
		manover_mode = 1;
		return;
	}
	switch(get_side_sensors_status()) {
		case 0:
			manover_mode = 5;
		break;
		case 1:
			manover_mode = 3;
		break;
		case 2:
			manover_mode = 4;
		break;
		case 3:
			manover_mode = 9;
		break;
	}
	manover_execution = 1;
}

void handle_mode_1() {
	switch(compute_mode()) {
		case 0: //stopped
			stop();
		break;
		case 1: //go forward
			center_servodrive();
			run_forward_full_mode(FULL_SPEED);
		break;
		case 2: //go forward and turn left
			turn_servodrive_left();
			if(run_forward_full_mode(FULL_SPEED, HALF_TURN_DIST)) {
				manover_execution = 0;
			}
		break;
		case 3: //go forward and turn right
			turn_servodrive_right();
			if(run_forward_full_mode(FULL_SPEED, HALF_TURN_DIST)) {
				manover_execution = 0;
			}
		break;
		case 4: //

		break;
		case 5: //go backward and turn left widely
			turn_servodrive_right();
			if(run_backward_full_mode(MID_SPEED, HALF_TURN_DIST)) {
				manover_mode = 2;
			}
		break;
		case 6: //go backward and turn left narrowly
			center_servodrive();
			if(run_backward_full_mode(MID_SPEED, FULL_TURN_DIST)) {
				manover_mode = 2;
			}
		break;
		case 7: //go backward and turn right widely
			turn_servodrive_left();
			if(run_backward_full_mode(MID_SPEED, HALF_TURN_DIST)) {
				manover_mode = 3;
			}
		break;
		case 8: //go backward and turn right narrowly
			center_servodrive();
			if(run_backward_full_mode(MID_SPEED, FULL_TURN_DIST)) {
				manover_mode = 3;
			}
		break;
		case 9:
			center_servodrive();
			if(run_backward_full_mode(MID_SPEED, GO_BACKWARD_DIST)) {
				manover_execution = 0;
			}
		break;
	}
}

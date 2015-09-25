#include "../Modes/mode_1.h"

#include "../Devices/step_motor.h"
#include "../Devices/servodrive.h"
#include "../Devices/proxi_switch.h"
#include "../Devices/buzzer.h"
#include "../Auxiliaries/delay.h"

volatile int manover_mode = 0;
volatile int manover_execution = 0;
volatile int distance_aux = 0;

int FULL_SPEED = 30000;
int MID_SPEED = 20000;
int SLOW_SPEED = 5000;

int FULL_TURN_DIST = 2000;
int HALF_TURN_DIST = 1000;
int GO_BACKWARD_DIST = 1000;

int get_side_sensors_status() {
	return proxi_switch_left_up_filtered()
			+ (2*proxi_switch_right_up_filtered());
}

void compute_mode() {
	if (manover_execution) {
		return;
	}
	if (!proxi_switch_front_down_filtered()) {
		manover_mode = 0;
		return;
	}
	if (!proxi_switch_front_up_filtered()) {
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
	compute_mode();
	switch(manover_mode) {
		case 0: //stopped
			stop();
		break;
		case 1: //go forward
			center_servodrive();
			run_forward_full_mode(FULL_SPEED);
		break;
		case 2: //go forward and turn left
			turn_servodrive_left();
			if(run_forward_full_mode_distance(FULL_SPEED, distance_aux)) {
				manover_execution = 0;
				distance_aux = 0;
			}
		break;
		case 3: //go forward and turn right
			turn_servodrive_right();
			if(run_forward_full_mode_distance(FULL_SPEED, distance_aux)) {
				manover_execution = 0;
				distance_aux = 0;
			}
		break;
		case 4: //

		break;
		case 5: //go backward and turn left widely
			turn_servodrive_right();
			if(run_backward_full_mode_distance(MID_SPEED, HALF_TURN_DIST)) {
				manover_mode = 2;
				distance_aux = HALF_TURN_DIST;
			}
		break;
		case 6: //go backward and turn left narrowly
			center_servodrive();
			if(run_backward_full_mode_distance(MID_SPEED, FULL_TURN_DIST)) {
				manover_mode = 2;
				distance_aux = FULL_TURN_DIST;
			}
		break;
		case 7: //go backward and turn right widely
			turn_servodrive_left();
			if(run_backward_full_mode_distance(MID_SPEED, HALF_TURN_DIST)) {
				manover_mode = 3;
				distance_aux = HALF_TURN_DIST;
			}
		break;
		case 8: //go backward and turn right narrowly
			center_servodrive();
			if(run_backward_full_mode_distance(MID_SPEED, FULL_TURN_DIST)) {
				manover_mode = 3;
				distance_aux = FULL_TURN_DIST;
			}
		break;
		case 9:
			center_servodrive();
			if(run_backward_full_mode_distance(MID_SPEED, GO_BACKWARD_DIST)) {
				manover_execution = 0;
			}
		break;
	}
}

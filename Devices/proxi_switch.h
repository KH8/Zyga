void init_proxi_switch();

int proxi_switch_front_up();
int proxi_switch_front_down();
int proxi_switch_left_up();
int proxi_switch_right_up();

int proxi_switch_front_up_filtered();
int proxi_switch_front_down_filtered();
int proxi_switch_left_up_filtered();
int proxi_switch_right_up_filtered();

void handle_proxi_switch();
void handle_proxi_switch_filter(int counter);

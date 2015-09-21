void init_step_motor();

void run_forward_full_mode(int sp);
void run_forward_half_mode(int sp);
void run_backward_full_mode(int sp);
void run_backward_half_mode(int sp);

void stop();

void handle_step_motor(long counter);

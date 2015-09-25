void init_step_motor();

void stop();

void run_forward_full_mode(int sp);
void run_forward_half_mode(int sp);
void run_backward_full_mode(int sp);
void run_backward_half_mode(int sp);

int run_forward_full_mode(int sp, int dist);
int run_forward_half_mode(int sp, int dist);
int run_backward_full_mode(int sp, int dist);
int run_backward_half_mode(int sp, int dist);

void handle_step_motor(int counter);

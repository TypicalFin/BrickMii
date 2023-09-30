#define VERSION "1.0"

#define STATE_WARNING 0
#define STATE_MAIN_MENU 1
#define STATE_CONFIRMING 2
#define STATE_BRICKING 3
#define STATE_BRICKING_DONE 4

extern int current_state;
static int main_menu_index;

void state_warning();
void state_main_menu();
void state_confirming();
void state_bricking();
void state_bricking_done();

void change_state(int new_state);
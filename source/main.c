#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "state.h"
#include "screen.h"

bool running = true;

int main(int argc, char **argv) {
    WPAD_Init();
    video_init();

	while (running) {
        WPAD_ScanPads();

        switch (current_state) {
            case STATE_WARNING:
                state_warning();
                break;
            case STATE_MAIN_MENU:
                state_main_menu();
                break;
            case STATE_CONFIRMING:
                state_confirming();
                break;
            case STATE_BRICKING:
                state_bricking();
                break;
            case STATE_BRICKING_DONE:
                state_bricking_done();
                break;
        }

		VIDEO_WaitVSync();
	}

    return 0;
}

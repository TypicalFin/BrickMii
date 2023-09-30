#include "state.h"
#include "screen.h"
#include "brick.h"

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

int current_state = STATE_WARNING;
static struct brick* current_brick;

static int clamp(int value, int min, int max) {
    const int t = value < min ? min : value;
    return t > max ? max : t;
}

static void print_choices(int current_index) {
    set_cursor(2, 0);

    for (int i = 0; i < brick_count; i++) {
        struct brick current = bricks[i];
        bool selected = i == current_index;

        printf("[%c] %s\n", (selected ? '+' : ' '), current.name);
    }
}

void state_warning() {
    set_cursor(0, 0);
    printf("Welcome to BrickMii!\n");
    printf("This program is designed to, well, brick your Wii.\n");
    printf("Please note that the creator of this program is not responsible\n");
    printf("for any damage caused by it. Proceed only if you know what you're doing.\n");
    printf("\n");
    printf("You have been warned!\n");
    printf("\n");
    printf("Press A to continue.\n");
    printf("Otherwise, press HOME to exit.\n");

    u32 pressed = WPAD_ButtonsDown(0);

    if (pressed & WPAD_BUTTON_A)
        change_state(STATE_MAIN_MENU);
    else if (pressed & WPAD_BUTTON_HOME)
        exit(0);
}

void state_main_menu() {
    set_cursor(0, 0);
    printf("BrickMii %s\n", VERSION);

    u32 pressed = WPAD_ButtonsDown(0);

    if (pressed & WPAD_BUTTON_UP)
        main_menu_index--;
    else if (pressed & WPAD_BUTTON_DOWN)
        main_menu_index++;

    main_menu_index = clamp(main_menu_index, 0, 2);
    print_choices(main_menu_index);

    printf("\n");
    printf("Press UP and DOWN to select a bricking method.\n");
    printf("Press A to continue.\n");
    printf("Press HOME to exit.\n");

    if (pressed & WPAD_BUTTON_A) {
        current_brick = &bricks[main_menu_index];
        change_state(STATE_CONFIRMING);
        return;
    }

    if (pressed & WPAD_BUTTON_HOME) {
        clear_framebuffer();
        set_cursor(0, 0);

        printf("Goodbye!\n");
        exit(0);
    }
}

void state_confirming() {
    if (current_brick == NULL) {
        change_state(STATE_MAIN_MENU);
        return;
    }

    set_cursor(0, 0);
    printf("Are you sure you want to brick your Wii\n");
    printf("using %s?\n", current_brick->name);
    printf("\n\nPress + to BRICK\n");
    printf("Press - to CANCEL\n");
    printf("\nDo note that the creator of this program is\n");
    printf("not responsible for any damage done to your Wii!");

    u32 pressed = WPAD_ButtonsDown(0);

    if (pressed & WPAD_BUTTON_PLUS) {
        change_state(STATE_BRICKING);
        return;
    }

    if (pressed & WPAD_BUTTON_MINUS) {
        current_brick = NULL;
        change_state(STATE_MAIN_MENU);
        return;
    }
}

void state_bricking() {
    if (current_brick != NULL) {
        set_cursor(0, 0);
        printf("Bricking...\n");

        int result = (*current_brick->execute)();
        current_brick = NULL;

        printf("Done!\n\n");

        printf("Return code: %d (%s)\n", result, (result == 0 ? "successful" : "failed"));
        printf("Press A to return to the main menu.\n");

        current_state = STATE_BRICKING_DONE;
    }
}

void state_bricking_done() {
    u32 pressed = WPAD_ButtonsDown(0);

    if (current_state == STATE_BRICKING_DONE && pressed & WPAD_BUTTON_A) {
        change_state(STATE_MAIN_MENU);
    }
}

void change_state(int new_state) {
    current_state = new_state;
    clear_framebuffer();
}
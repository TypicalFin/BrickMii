#include "screen.h"

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

GXRModeObj* mode;
void* xfb;

void video_init() {
    VIDEO_Init();

    mode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(mode));

    console_init(xfb, 20, 20, mode->fbWidth, mode->xfbHeight, mode->fbWidth * VI_DISPLAY_PIX_SZ);

    VIDEO_Configure(mode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();

    VIDEO_WaitVSync();

    if (mode->viTVMode & VI_NON_INTERLACE)
        VIDEO_WaitVSync();
}

void set_cursor(int row, int column) {
    printf("\x1b[%d;%dH", row, column);
}

void clear_framebuffer() {
    VIDEO_ClearFrameBuffer(mode, xfb, COLOR_BLACK);
}
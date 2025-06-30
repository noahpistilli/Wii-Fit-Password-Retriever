#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogcsys.h>
#include <iostream>
#include "save.h"

static void *xfb = nullptr;
static GXRModeObj *rmode = nullptr;

[[noreturn]] void poll_home_button() {
    while (true) {
        WPAD_ScanPads();
        const u32 pressed = WPAD_ButtonsDown(0);
        if (pressed & WPAD_BUTTON_HOME)
            exit(0);
        VIDEO_WaitVSync();
    }
}

int main() {
    VIDEO_Init();
    WPAD_Init();
    CONF_Init();
    ISFS_Initialize();

    rmode = VIDEO_GetPreferredMode(nullptr);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    console_init(xfb,20,20,rmode->fbWidth-20,rmode->xfbHeight-20,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);
    VIDEO_SetBlack(false);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Wii Fit Password Retriever - (c) 2025 Noah Pistilli" << std::endl;
    std::cout << "v0.1" << std::endl;
    std::cout << std::endl;

    auto save = new SaveSelectModal();
    if (save->HasSave()) {
        std::cout << "No saves available." << std::endl;
    }

    save->Start();
    poll_home_button();
}
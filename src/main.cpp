#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

int main(int argc, char* argv[]) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    fsInit();

    FS_Archive arc = 0;
    Result ret = archiveMount(ARCHIVE_SAVEDATA, fsMakePath(PATH_EMPTY, ""), "test");
    printf("archiveMount: %s! (0x%lx)", R_FAILED(ret) ? "failed" : "success", ret);

    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) {
            break;
        }
    }
    
    fsExit();
    gfxExit();
    return 0;
}
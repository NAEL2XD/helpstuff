#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

int main(int argc, char* argv[]) { 
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    fsInit();

    FS_Path path = fsMakePath(PATH_EMPTY, "");
    Result ret = FSUSER_FormatSaveData(ARCHIVE_SAVEDATA, path, 1024*128, 1, 1, 3, 3, false);
    printf("FSUSER_FormatSaveData: %s! (0x%lx)", R_FAILED(ret) ? "failed" : "success", ret);

    ret = archiveMount(ARCHIVE_SAVEDATA, path, "test");
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
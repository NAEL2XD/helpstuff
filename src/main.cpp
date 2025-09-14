#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <fstream>

int main(int argc, char* argv[]) { 
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    fsInit();

    FS_Path path = fsMakePath(PATH_EMPTY, "");
    Result ret = FSUSER_FormatSaveData(ARCHIVE_SAVEDATA, path, 0x200, 1, 1, 3, 3, false);
    printf("FSUSER_FormatSaveData: %s! (0x%lx)\n", R_FAILED(ret) ? "failed" : "success", ret);

    ret = archiveMount(ARCHIVE_SAVEDATA, path, "test");
    printf("archiveMount: %s! (0x%lx)\n", R_FAILED(ret) ? "failed" : "success", ret);

    std::ofstream file("test:/test.txt");
    if (file.is_open()) {
        file << "So this is my awesome data";
        file.flush();
        printf("file.flush(): %s! (0x%lx)\n", file.good() ? "success": "failed");
    }

    ret = archiveCommitSaveData("test");
    printf("archiveCommitSaveData: %s! (0x%lx)\n", R_FAILED(ret) ? "failed" : "success", ret);

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
#include "filesystem.h"

void fsInit(void) {
    Disk = {0};
    
    FILE *f = fopen("dump.img", "a+");
    fclose(f);
    
    f = fopen("dump.img", "rb");
    fread(&Disk, sizeof(Tdisk), 1, f);
    fclose(f);
    return 0;
}

int GetAllFreeMemory() {
    int counter = 0;
    for(int i = 0; i < 512; i++) {
        for(int j = 0; j < 512; j++) {
            if(Disk.superblock.cluster[i].sector[j] == 0) {
                counter += 1;
            }
        }
    }
    
    return counter;
}

int GetFreeClusters() {
    int counter = 0;

    for(int i = 0; i < 512; i++) {
        if(Disk.superblock.cluster[i].used == 0) {
            counter += 1;
        }
    }
    
    return counter;
}

int GetFreeEntries() {
    int counter = 0;
    
    for(int i = 0; i < 128; i++) {
        if(Disk.root.entry[i].used == 0) {
            counter += 1;
        }
    }
    
    return counter;
}

int CreateFile(char path) {
    if(path == "") return 1;
    
    if(GetFreeEntries() == 0) return 2;
}

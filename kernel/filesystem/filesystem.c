#include "filesystem.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

Tdisk Disk = {0};

void fileSystemInit(void) {
    
    FILE *f = fopen("dump.img", "a+");
    fclose(f);
    
    f = fopen("dump.img", "rb");
    fread(&Disk, sizeof(Tdisk), 1, f);
    fclose(f);
}

int getAllFreeMemory() {
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

int getFreeCluster() {
    for(int i = 0; i < 512; i++) {
        if(Disk.superblock.cluster[i].used == 0) {
            return i;
        }
    }
    
    return -1;
}

int getFreeEntry() {
    for(int i = 0; i < 128; i++) {
        if(Disk.root.entry[i].path[0] == "\0") {
            return i;
        }
    }
    
    return -1;
}

int findEntry(char *path) {
    for(int i = 0; i < 128; i++) {
        if(strcmp(Disk.root.entry[i].path, path)) {
            return i;
        }
    }
    
    return -1;
}

int createFile(char *path, int file_type) {
    if(path == NULL) return 1;
    
    int free_ent = getFreeEntry();
    if(free_ent == -1) return 2;
    
    int free_cl = getFreeCluster();
    if(free_cl == -1) return 3;
    
    Tfile_entry *cur = &Disk.root.entry[free_ent];
    strncpy(cur->path, path, sizeof(cur->path) - 1);
    cur->path[sizeof(cur->path) - 1] = '\0';
    
    cur->file_type = file_type;
    cur->start_cluster = free_cl;
    
    return 0;
    
}

int deleteFile(char *path) {
    if(path == NULL) return 1;
    
    int pos = findEntry(path);
    Tcluster *cur_cl = &Disk.superblock.cluster[pos];
    while(cur_cl->next != NULL) {
        cur_cl->used = 0;
        cur_cl = cur_cl->next;
    }
    
    Tfile_entry *cur = &Disk.root.entry[pos];
    cur->path[0] = "\0";
    cur->file_type = -1;
    cur->start_cluster = -1;
    
    return 0;
}

int write(size_t cl_off, unsigned char *buffer, size_t size) {
    if(buffer == NULL || cl_off == -1 || size == 0) return 1;
    
    size_t cl_count = ceil(size / 512);
    size_t cur_index = cl_off;
    Tcluster *cur_cl = &Disk.superblock.cluster[cur_index];
    for(size_t i = 0; i <= cl_count; i++) {
        memcpy(cur_cl->sector, buffer + (512 * i), 512);
        cur_cl->used = 1;
        cur_cl = cur_cl->next;
    }
    
    return 0;
}

int read(size_t cl_off, unsigned char *buffer, size_t size) {
    if(buffer == NULL || cl_off == -1 || size == 0) return 1;
    
    size_t cl_count = ceil(size / 512);
    size_t cur_index = cl_off;
    Tcluster *cur_cl = &Disk.superblock.cluster[cur_index];
    for(size_t i = 0; i <= cl_count; i++) {
        memcpy(buffer, cur_cl->sector + (512 * i), 512);
        cur_cl = cur_cl->next;
    }
    
    return 0;
}

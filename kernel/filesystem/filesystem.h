#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stddef.h>

typedef struct {
    char name[32];
    int size;
} Tdisk_header;

typedef struct {
    char path[64];
    int file_type; //1 is executable, 2 is text file
    int start_cluster;
} Tfile_entry;

struct Fcluster {
    unsigned char sector[512];
    int used;
    struct Fcluster *next;
};

typedef struct Fcluster Tcluster;

typedef struct {
    Tcluster cluster[512];
} Tsuperblock;

typedef struct {
    Tfile_entry entry[128];
} Troot;

typedef struct {
    Tsuperblock superblock;
    Troot root;
    Tdisk_header header;
} Tdisk;

extern Tdisk Disk;

int createFile(char *path, int file_type);

int deleteFile(char *path);

int write(size_t cl_off, unsigned char *buffer, size_t size);

int read(size_t cl_off, unsigned char *buffer, size_t size);

void fileSystemInit(void);

int getAllFreeMemory();

#endif

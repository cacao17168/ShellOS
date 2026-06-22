#ifndef FILESYSTEM_H
#define FILESYSTEM_H

typedef struct {
    char name[32];
    int size;
} Tdisk_header;

typedef struct {
    char name[32];
    int file_type;
    int start_cluster;
} Tfile_entry;

typedef struct {
    unsigned char sector[512];
    int used;
} Tcluster;

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

Tdisk Disk;

#endif

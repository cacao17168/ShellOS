#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 128

typedef int (*func)(int argc, char** args);

typedef struct {
    char* name;
    func command;
} Node;

extern Node cmd_table[TABLE_SIZE];

typedef struct {
    const char *name;
    func pcmd;
} FuncEntry;

func find_command(const char* name);

unsigned int hash(const char* key);

int run_command(const char* name, int argc, char** argv);

int hash_table_init();

int hash_quit();

#endif

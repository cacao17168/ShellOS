#include "hash_table.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Node cmd_table[TABLE_SIZE];

int cmd_help(int argc, char** argv) {
    printf("Welcome to ShellOS! This program emulates operating system work.\n");
    return 0;
}

int cmd_quit(int argc, char** argv) {
    return 18;
}

#include "registry.c"

func find_command(const char* name) {
    unsigned int idx = hash(name) % TABLE_SIZE;
    unsigned int offset = 0;
    
    unsigned int pos = (idx + offset) % TABLE_SIZE;
    
    Node *cur = &cmd_table[pos];
    
    while(cur->name != NULL) {
        pos = (idx + offset) % TABLE_SIZE;
        
        cur = &cmd_table[pos];
        
        if(strcmp(cur->name, name) == 0) {
            return cur->command;
        } else {
            offset++;
        }
    }
    
    return NULL;
}

unsigned int hash(const char* key) {
    unsigned int hash_val = 0;
    while(*key) {
        hash_val += *key;
        key++;
    }
    return hash_val;
}

int new_node(const char* name, func command_name) {
    unsigned int idx = hash(name) % TABLE_SIZE;
    unsigned int offset = 0;
    
    if(idx > TABLE_SIZE) {
        return 1;
    }
    
    Node *cur = &cmd_table[idx];
    
    if(cur->name == NULL) {
        cur->name = name;
        cur->command = command_name;
    } else {
        while(cur->name != NULL) {
            unsigned int pos = (idx + offset) % TABLE_SIZE;
        
            if(strcmp(cur->name, name) == 0) {
                return 2;
            }
        
            offset++;
            if(pos > TABLE_SIZE) {
                return 1;
            }
            cur = &cmd_table[pos];
        }
        cur->name = name;
        cur->command = command_name;
    }
    
    return 0;
}

int run_command(const char* name, int argc, char** argv) {
    func f = find_command(name);
    
    if(f == NULL) {
        printf("Bruh. Unknown command.\n");
        return 1;
    }
    
    return f(argc, argv);
}

int hash_table_init() {
    for(int i = 0; command_registry[i].name != NULL; i++) {
        new_node(command_registry[i].name, command_registry[i].pcmd);
    }
    return 0;
}

int hash_quit() {
    int i = 0;
    
    return 0;
}

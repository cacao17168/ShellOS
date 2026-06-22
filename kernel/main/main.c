#include "hash_table.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    char cmd[256] = {0};
    
    hash_table_init();
    
    while(1) {
        printf("~$ ");
        fgets(cmd, sizeof(cmd), stdin);
        
        cmd[strcspn(cmd, "\n")] = '\0';
        
        int status = run_command(cmd, 1, NULL);
        if(status == 18) break;
    }
    hash_quit();
}

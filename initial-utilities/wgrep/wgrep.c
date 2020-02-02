#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool match(char *pattern, char *target) {
    for(int p_i = 0, t_i = 0; target[t_i] != '\0'; t_i++) {
        if(pattern[p_i] == target[t_i]) {
            p_i++;
        } else {
            p_i = 0;
        }

        if(pattern[p_i] == '\0') {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {

    if(argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    if(argc == 2) {
        char *line = NULL;
        size_t len = 0;

        while(getline(&line, &len, stdin) != -1 ) {
            if(match(argv[1], line)) {
                printf(line);
            }
        }
    }

    for(int fileNo = 2; fileNo < argc; fileNo++) {
        // Deal with each file
        char *filePath = (char *) malloc((3 + strlen(argv[fileNo]))*sizeof(char));
        filePath[0] = '\0';
        filePath = strcat(filePath, "./");
        filePath = strcat(filePath, argv[fileNo]);
        FILE* fp = fopen(filePath, "r");

        if(fp == NULL) {
            free(filePath);
            printf("wgrep: cannot open file\n");
            return 1;
        }

        char *line = NULL;
        size_t len = 0;

        while(getline(&line, &len, fp) != -1 ) {
            if(match(argv[1], line)) {
                printf(line);
            }
        }
        free(filePath);
        fclose(fp);

    }
    return 0;

}


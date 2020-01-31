#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int BUFFER_SIZE = 16;
    if(argc == 0) return 0;

    for(int fileNo = 1; fileNo < argc; fileNo++) {
        // Deal with each file
        // char filePath[3+strlen(argv[fileNo])] = "./";
        char *filePath = (char *) malloc((3 + strlen(argv[fileNo]))*sizeof(char));
        filePath = strcat(filePath, argv[fileNo]);
        FILE* fp = fopen(filePath, "r");

        if(fp == NULL) {
            free(filePath);
            printf("wcat: cannot open file\n");
            return 1;
        }

        char buffer[BUFFER_SIZE];
        while(fgets(buffer, BUFFER_SIZE, fp)) {
            printf(buffer);
        }
        free(filePath);
        fclose(fp);
    }

    return 0;
}

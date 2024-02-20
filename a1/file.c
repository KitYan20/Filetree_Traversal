#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void search_file(const *filename,const char *pattern){
    FILE *file = fopen(filename,"r");
    if (file == NULL){
        perror("Error opening file");
        return;
    }
    char line[512];
    int line_number = 0;
    while (fgets(line,sizeof(line),file)){
        line_number++;
        if (strstr(line,pattern) != NULL){
            printf("Filename: %s\n Line Number: %d\n line: %s\n", filename, line_number, line);
        }
    }
    fclose(file);
}
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "file.h"
#include "directory.h"

int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr,"Needs more than two arguments\n");
        return 1;
    };
    const char *pathname = argv[1];
    const char *pattern = argv[2];
    search_directory(pathname,pattern);
    return 0;
}
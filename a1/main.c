#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "directory.h"

int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr,"Needs more than two arguments\n");
        return 1;
    };
    int ret;
    const char *pathname = argv[1];
    const char *pattern = argv[2];
    myftw(pathname,myfunc);
    return 0;
}
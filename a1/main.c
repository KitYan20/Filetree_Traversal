#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "file.h"
#include "directory.h"

int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr,"Needs more than two arguments",argv[0]);
        return 1;
    };
    return 0;
}
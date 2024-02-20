#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void search_directory(const char *pathname,const char* pattern){
    DIR *directory =opendir(pathname);
    struct dirent *entry;


    if (directory == NULL){
        printf("Error opening the directory\n");
        exit(-1);
    }
    //Read in the next entry in the directory
    //Returns null when it reads every entry until the end
    while((entry = readdir(directory)) != NULL){
        if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }
        char *extension = strrchr(entry->d_name,'.');
        if (extension != NULL && strcmp(extension,".c") == 0){
            printf("Name: %s\n" ,entry->d_name);
            search_file((char*)entry->d_name, pattern);
        }
        
        
        
    }
    if (closedir(directory) < 0){
        printf("Error closing directory\n");
        exit(-1);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
// #include "directory.h"

typedef int Myfunc(const char*,const char*);
static Myfunc myfunc;
static int myftw(const char *, Myfunc *);
static int dopath(Myfunc *);
static char *fullpath;
static size_t pathlen;

static int myftw(const char *pathname, Myfunc *func){
    pathlen = PATH_MAX + 1;
    fullpath = malloc(pathlen);
    if (pathlen <= strlen(pathname)){
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath,pathlen)) == NULL){
            printf("realloc failed");
        }
    }
    strcpy(fullpath,pathname);
    return dopath(func);
}

static int dopath(Myfunc *func){
    DIR *directory;
    struct dirent *entry;
    int ret,n;
    
    if ((ret = func(fullpath,"s")) != 0){
        return ret;
    }
    n = strlen(fullpath);

    if (n + NAME_MAX + 2 > pathlen){
        pathlen *= 2;
        if ((fullpath = realloc(fullpath,pathlen)) == NULL){
            printf("realloc failed\n");
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;

    if ((directory = opendir(fullpath)) == NULL){
        return func(fullpath,"s");
    }
    while( (entry = readdir(directory))!= NULL){
            if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
                continue;
            }
            strcpy(&fullpath[n],entry->d_name);
            if ((ret = dopath(func)) != 0)
                break;
            
    }
    
    
    fullpath[n-1] = 0;
    
    if (closedir(directory) < 0){
        printf("can’t close directory %s", fullpath);
    }
    return ret;
}
static int myfunc(const char* pathname, const char *pattern){
    FILE *file = fopen(pathname,"r");
    if (file == NULL){
        printf("Error opening files either a directory or not a readable file\n");
        return 0;
    }
    char line[512];
    int line_number = 0;    
    while (fgets(line,sizeof(line),file)){
        line_number++;
        if (strstr(line,pattern) != NULL){
            printf("Line: %s Path: %s",line,pathname); 
            printf("\n");         
        }       
        
    }
    fclose(file);
    return 0;
}
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
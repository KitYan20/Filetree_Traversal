#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef int Myfunc(const char*,int,const char*);
static Myfunc myfunc;
int myftw(const char *, Myfunc *);
static int dopath(Myfunc *);

#define FTW_F 1 /* file other than directory */
#define FTW_D 2 /* directory */
#define FTW_DNR 3 /* directory that can’t be read */
#define FTW_NS 4 /* file that we can’t stat */
#define PATH_MAX 4096

static char *fullpath;
static size_t pathlen;

int myftw(const char *pathname, Myfunc *func){
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

    if ((ret = func(fullpath,FTW_D,"s")) != 0){
        return ret;
    }
    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen){
        pathlen *= 2;
        if ((fullpath = realloc(fullpath,pathlen)) == NULL){
            printf("realloc failed");
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;

    if ((directory = opendir(fullpath)) == NULL){
        return func(fullpath,FTW_DNR,"s");
    }
    while( (entry = readdir(directory))!= NULL){
        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }
        strcpy(&fullpath[n],entry->d_name);
        if ((ret = dopath(func)) != 0){
            break;
        }
    }
    fullpath[n-1] = 0;
    if (closedir(directory) < 0){
        printf("can’t close directory %s", fullpath);
    }
    return ret;
}
static int myfunc(const char* pathname, int type,const char *pattern){
    FILE *file = fopen(pathname,"r");
    if (file == NULL){
        perror("Error opening file");
        return -1;
    }
    char line[512];
    
    // char path[1000]; 
    int line_number = 0;
    
    // strcat(path,pathname);
    // strcat(path,"/");
    // strcat(path, pathname);
    
    while (fgets(line,sizeof(line),file)){
        line_number++;
        if (strstr(line,pattern) != NULL){
            printf("Line: %s Path: %s",line,pathname); 
            printf("\n");
            
        }       
        
    }
    // path[0] = '\0';
    
    fclose(file);
    return 0;
}
// #define MAX_PATH_LENGTH 1024

// void search_file(const char *filename,const char *pathname, const char *pattern){
//     FILE *file = fopen(filename,"r");
//     if (file == NULL){
//         perror("Error opening file");
//         return;
//     }
//     char line[512];
    
//     char path[1000]; 
//     int line_number = 0;
    
//     strcat(path,pathname);
//     strcat(path,"/");
//     strcat(path, filename);
    
//     while (fgets(line,sizeof(line),file)){
//         line_number++;
//         if (strstr(line,pattern) != NULL){
//             printf("Line: %s Path: %s",line,path); 
//             printf("\n");
//         }       
        
//     }
//     path[0] = '\0';
    
//     fclose(file);
// }

// void search_directory(const char *pathname,const char* pattern){
//     DIR *directory = opendir(pathname);
//     struct dirent *entry;


//     if (!directory){
//         return;
//     }
//     //Read in the next entry in the directory
//     //Returns null when it reads every entry until the end
//     printf("Reading files in %s\n",pathname);
    
//     char path[1000];
//     while( (entry = readdir(directory))!= NULL){
//         // if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
//         //     continue;
//         // }
        
//         // snprintf(path,sizeof(path),"%s/%s",pathname,entry->d_name);
//         // printf("Name %s\n",path);
//         struct stat statbuf;
        
//         // 4 will indicate it's a directory
//         if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
//             //printf("Path: %s Name: %s Type %d\n" ,pathname, entry->d_name,entry->d_type);
//             // search_directory(path,pattern);
//             strcat(path,pathname);
//             strcat(path, "/");
//             strcat(path,entry->d_name);
//             search_directory(path,pattern);
          
//         }

//         search_file(entry->d_name,pathname,pattern);
//         entry = readdir(directory);
//     }
    
//     closedir(directory);
// }

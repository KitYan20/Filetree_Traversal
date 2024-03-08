#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "directory.h"
#define ARRAY_SIZE 100
typedef int Myfunc(const char*,const char*,const char*);
Myfunc myfunc;
int myftw(const char *, const char*, const char* ,int, Myfunc *);
int dopath(Myfunc *, const char*, const char*,int);
char *fullpath;
size_t pathlen;
//A helper function to call the main dopath function to perform file traversal
int myftw(const char *pathname, const char *pattern, const char *filetype, int symbolic_link, Myfunc *func){
    pathlen = PATH_MAX + 1;
    fullpath = malloc(pathlen);
    if (pathlen <= strlen(pathname)){
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath,pathlen)) == NULL){
            printf("realloc failed");
        }
    }
    // printf("%d\n", symbolic_link);
    strcpy(fullpath,pathname);
    return dopath(func,pattern,filetype,symbolic_link);
}


int dopath(Myfunc *func, const char *pattern,const char* filetype,int symbolic_link){
    DIR *directory;
    struct dirent *entry;
    struct stat statbuf;
    int ret,n;
    long inode_array[ARRAY_SIZE];
    
    //It's a directory
    if ((ret = func(fullpath,pattern,filetype)) != 0){
        return ret;
    }
    //Get the length of the current path
    n = strlen(fullpath);
    if (n + 1064 + 2 > pathlen){
        pathlen *= 2;
        if ((fullpath = realloc(fullpath,pathlen)) == NULL){
            printf("realloc failed\n");
        }
    }
    //Do a slash after the path to get ready to append the next file or directory
    fullpath[n++] = '/';
    //End it with a 0 to indicate the end of the path
    fullpath[n] = 0;
    //The function to open and write a file given that its not a directory that it traversed to or can't read directory
    if ((directory = opendir(fullpath)) == NULL){
        return func(fullpath,pattern,filetype);
    }
    int i = 0;
    long i_node;
    int found = 0;
    //Main function to do file tree traversal 
    while((entry = readdir(directory))!= NULL){
            //Do not include . or .. for our file traversal
            if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
                continue;
            }
            //Append the current file/directory name to our path
            strcpy(&fullpath[n],entry->d_name);
            //stat our full path to get information on the file/directory eg inodes
            stat(fullpath,&statbuf);   
            // printf("Inode iteration inode[%d]: %ld %s\n",i,inode_array[i],fullpath);  
            if (lstat(fullpath,&statbuf) == 0){
                //Get the inode of the current file type
                inode_array[i++] = (long)statbuf.st_ino;
                //Check if its not a directory so it has to be a regular file
                if (S_ISDIR(statbuf.st_mode) == 0){
                    //Checks if its a symbolic link file but we're not checking it depending is -l flag is specified
                    if (S_ISLNK(statbuf.st_mode) && (symbolic_link == 0)){
                        // printf("It's a symbolic but we're not checking");
                        continue;
                    }
                }
                //Checks if its a symbolic link directory and -l flag is specified
                if (S_ISDIR(statbuf.st_mode) == 1 && S_ISLNK(statbuf.st_mode) && symbolic_link == 1 ){
                        //printf("It's a symbolic directory");
                        //Iterating over the list of i-nodes for each file
                        for (int j = 0; j < i; j++){
                            //printf("I-node %ld %ld\n",inode_array[j],(long)statbuf.st_ino);
                            //If the i-nodes been visited, we shouldn't visit again resulting in a infinite loop
                            if (inode_array[j] == (long)statbuf.st_ino){
                                    found = 1;
                                    break;  
                            }
                        }
                        if (found == 1){
                            ret = 0;
                            if ((ret = dopath(func,pattern,filetype,symbolic_link)) != 0){
                                break;
                            } 
                        }                    
                }
                //Skip over the symbolic link directory is -l flag is not specified
                else if (S_ISDIR(statbuf.st_mode) == 1 && S_ISLNK(statbuf.st_mode) && symbolic_link == 0){
                    continue;
                }
                
            }
            if ((ret = dopath(func,pattern,filetype,symbolic_link)) != 0){//Time to exit out of the directory
                break; //Time to leave 
            }     
    } 
    fullpath[n-1] = 0; //Erase everything from the slash onwards
    if (closedir(directory) < 0){
        printf("can’t close directory %s", fullpath);
    }
    return ret;
}
int myfunc(const char* pathname, const char *pattern,const char *filetype){
    int n = strlen(pathname);
    const char *file_extension = &pathname[n-1];//Get the filetype extension
    FILE *file = fopen(pathname,"r"); //Open up the file to read
    
    if (file == NULL){//If file returns NULL, then its not a regular file so we go back to file traversal again
        //fprintf(stderr,"Error opening files either a directory or not a readable file\n");
        return 0;   
    }
    else{//It is a file
        if (filetype == NULL){//Checking if file type is not specified in command line basically search for all files
            char line[512];
            int line_number = 0;
            while (fgets(line,sizeof(line),file)){//Use a while loop to get the line on each file
                if (wildcard(line,(char*)pattern) == 1){//Checks if it matches with regex or alphanumerical characters
                    printf("Line: %s Path: %s",line,pathname); 
                    printf("\n");         
                }           
            }
        
        }//Same thing here but with file type specified in command line only search for specified file type extensions
        else if (strcmp(file_extension,filetype) == 0){
            char line[512];
            while (fgets(line,sizeof(line),file)){
                if (wildcard(line,(char*)pattern) == 1){
                    printf("Line:%s Path:%s\n",line,pathname); 
                            
                }           
            }
            
        }
    }
    fclose(file);//close the file
    return 0;
}
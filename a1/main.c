#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include "directory.h"

int main(int argc, char *argv[]){
    /*
    Options for -f and -l
    either have -f with c, h, S and -l -> search all the specified file type with symbolic links
    have -f with c,h,s and not -l -> search all the specified file type with no symbolic links
    have no -f and have -l -> search for all regular files and symbolic links
    have no -f and have no -l -> search for all regular files with no symbolic links

    */
    int opt;
    //path of directory
    const char *pathname = NULL;
    //Get the file type if -f flag is intialized
    const char *file_type = NULL;
    //get the search string "s"
    const char *pattern = NULL;
    int include_links = 0;

    while((opt = getopt(argc,argv, "p:f:s:l")) != -1){
        switch(opt){
            case 'p':
                pathname = optarg;
                break;
            case 'f':
                file_type = optarg;
                break;
            case 's':
                pattern = optarg;
                break;
            case 'l':
                include_links = 1;
                break;
            case '?':
                if (optopt == 'p'){
                    fprintf(stderr,"Option -%c requires a pathname.\n",optopt);
                }if (optopt = 'f'){
                    fprintf(stderr,"Option -%c requires a file type.\n",optopt);
                }if (optopt = 's'){
                    fprintf(stderr,"Option -%c requires a string to match.\n",optopt);
                }else{
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                }
                return 1;
            default:
                abort();
        }
    }
    
    printf("finds -p %s -f %s -l %d -s %s\n",pathname,file_type,include_links,pattern);
    // const char *pathname = argv[1];
    // const char *pattern = argv[2];
    myftw(pathname,pattern,file_type,myfunc);
    return 0;
}
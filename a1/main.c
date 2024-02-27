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
    // if (argc < 3){
    //     fprintf(stderr,"Needs more than two arguments\n");
    //     return 1;
    // }
    int opt;
    char *pathname = NULL;
    char *suffix = NULL;
    char *search_string = NULL;
    int include_links = 0;
    while((opt = getopt(argc,argv, "p:f:s:l")) != -1){
        switch(opt){
            case 'p':
                pathname = optarg;
                break;
            case 'f':
                suffix = optarg;
                break;
            case 's':
                search_string = optarg;
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
    
    printf("finds -p %s -f %s -l %d -s %s\n",pathname,suffix,include_links,search_string);
    // const char *pathname = argv[1];
    // const char *pattern = argv[2];
    // myftw(pathname,pattern,myfunc);
    return 0;
}
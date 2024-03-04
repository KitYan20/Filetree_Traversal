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
    have -f with c,h,s and not -l -> search all the specified file type with no symbolic links -> done
    have no -f and have -l -> search for all regular files with symbolic links
    have no -f and have no -l -> search for all regular files with no symbolic links -> done

    */
    int opt;
    //path of directory
    const char *pathname = NULL;
    //Get the file type if -f flag is intialized
    const char *file_type = NULL;
    //get the search string "s"
    const char *pattern = NULL;
    int include_links = 0;

    // if (argc < 2){
    //     fprintf(stderr,"Need to pass in arguments\n");
    //     exit(EXIT_FAILURE);
    // }
    // while((opt = getopt(argc,argv, "p:f:s:l")) != -1){
    //     switch(opt){
    //         case 'p':
    //             pathname = optarg;
    //             break;
    //         case 'f':
    //             if (optarg[0] != 'c' && optarg[0] != 'h' && optarg[0] != 'S' && optarg[0] != 's'){
    //                 fprintf(stderr,"Option -%c requires either c, h, s as argument for f\n",optopt);
    //                 return 1;
    //             }
    //             file_type = optarg;
    //             break;
    //         case 's':
    //             pattern = optarg;
    //             break;
    //         case 'l':
    //             include_links = 1;
    //             break;
    //         case '?':
    //             if (optopt == 'p'){
    //                 fprintf(stderr,"Option -%c requires a pathname.\n",optopt);
    //                 return 1;
    //             }if (optopt = 's'){
    //                 fprintf(stderr,"Option -%c requires a string to match.\n",optopt);
    //                 return 1;
    //             }if (optopt = 'f'){
    //                 fprintf(stderr,"Option -%c requires file type.\n",optopt);
    //                 return 1;
    //             }else{
    //                 fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
    //                 return 1;
    //             }
    //         default:
    //             //abort();
    //             exit(EXIT_FAILURE);
    //     }
    // }
    
    //printf("finds -p %s -f %s -l %d -s %s\n",pathname,file_type,include_links,pattern);
    //myftw(pathname,pattern,file_type,include_links,myfunc);
    wildcard("a9b","a.b");
    wildcard("ab","a.b");
    wildcard("abb","a.b");
    wildcard("greatSentenceaXbcool","a.b");
    return 0;
}
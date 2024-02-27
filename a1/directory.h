#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef int myfunc(const char*,int,const char*);
int myftw(const char *pathname, Myfunc *func);
static int myfunc(const char* pathname, int type,const char *pattern);
static int dopath(Myfunc *func);

#endif
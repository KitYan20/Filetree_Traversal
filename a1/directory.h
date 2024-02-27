#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef int Myfunc(const char *, const char *);
Myfunc myfunc;
int myftw(const char *pathname, Myfunc *func);
int dopath(Myfunc *func);
#endif
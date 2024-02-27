#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef int Myfunc(const char *, const char *);
Myfunc myfunc;
int myftw(const char *pathname, const char *pattern, Myfunc *func);
int dopath(Myfunc *func, const char *pattern);
#endif
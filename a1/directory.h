#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <stdbool.h>
typedef int Myfunc(const char *, const char *, const char*);
Myfunc myfunc;
int myftw(const char *pathname, const char *pattern, const char *filetype, int symbolic_link, Myfunc *func);
int dopath(Myfunc *func, const char *pattern, const char *filetype, int symbolic_link);
bool wildcard(const char* str, const char* pattern);
#endif
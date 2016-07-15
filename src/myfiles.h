#ifndef __MYFILES_H
#define __MYFILES_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#endif
char* prog_name = NULL;
void usage(void);
void err_sys(const char* x);

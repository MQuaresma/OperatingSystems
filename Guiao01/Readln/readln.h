#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/unistd.h>     /* chamadas ao sistema: defs e declaraçoes essenciais */
#include <sys/fcntl.h>      /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

//int     open(const char *path, int oflag [,mode_t mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int     close(int fildes);
ssize_t readln(int, void*, size_t);
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/unistd.h>     /* chamadas ao sistema: defs e declaraçoes essenciais */
#include <sys/fcntl.h>      /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include "guiao01.h"


/* 10mb: writes a file with 10Mb worth of characters
 * the filename is provided via the arguments
 */
int main(int argc, char *argv[]){

    int filde;
    int size = 10*1024*1024; // numbers of chars to be written 10^7 since each char uses 1byte of space
    char buf[MAXLINE];

    for(int i = 0; i < MAXLINE; i ++) buf[i] = 'a';

    if(argc <= 1){
        fprintf(stderr, "Not enought arguments provided\n");
        exit(1);
    }

    filde = open(*++argv, O_WRONLY);

    // If the file doesn't exist exit with error
    if(filde < 0){
        fprintf(stderr, "File not found\n");
        exit(1);
    }

    size /= MAXLINE;

    for(int i = 0; i < size; i++) write(filde, buf, MAXLINE);

    close(filde);
    exit(0);
}

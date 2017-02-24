#include "guiao01.h"

ssize_t readln(int, void*, size_t);
size_t parse(char*);

int main(int argc, char *argv[]){

    size_t block = 100, r;
    int fildes=0, line = 1;
    char *buf=(char*)malloc(sizeof(char)*block);

    if(argc <= 1){
        fprintf(stderr, "Not enought arguments provided\n");
        exit(1);
    }

    if(--argc > 0){
        ++ argv;
        fildes = open(*argv, O_RDONLY);

        if(fildes < 0){
            fprintf(stderr, "File (%s) not found\n", *argv);
            exit(1);
        }
        else printf("\t\n-------File: %s------\n",*argv);
    }

    while((r = readln(fildes, buf, block))>0){
        printf("\t%d %s", ++line, buf);
        //write(1, buf, r);
    }    
}


/* reads until a new line char is found or until block is reached */
ssize_t readln(int fildes, void *buf, size_t block){

    ssize_t i, r;
    char *st=buf;

    for(i = 0; i < block && (r=read(fildes, st+i, 1)) > 0 && *(st+i) != '\n'; i ++);

    if(*(st+i) == '\n') i ++;
    *(st+i) = '\0';

    return i;
}

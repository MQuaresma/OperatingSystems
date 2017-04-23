#include "nl-v2.h"

int main(int argc, char *argv[]){

    ssize_t r;
    int fildes=0, line;
    char *buf;
    char no[SIZE];
    struct buffer_t *b = (struct buffer_t *)malloc(sizeof(struct buffer_t));

    b->in=b->out=b->start=NULL;

    while(--argc > 0){
        ++ argv;
        fildes = open(*argv, O_RDONLY);

        if(fildes < 0){
            fprintf(stderr, "File (%s) not found\n", *argv);
            exit(1);
        }
        else printf("\t\n-------File: %s------\n",*argv);
        
        no[0] = '\t';
        line = 1;
        while((r = readln(fildes, b, &buf))>0){
            itoa(line++, no+1);
            write(1, no, strlen(no));
            write(1, buf, r);
        } 
    
    }   
}

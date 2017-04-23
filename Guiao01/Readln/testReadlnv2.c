#include "readlnv2.h"

main(){

    char *buf;
    ssize_t red;
    struct buffer_t *b = (struct buffer_t *)malloc(sizeof(struct buffer_t));
    if(!b){
        fprintf(stderr, "Couldn't create buffer\n");
        exit(1);
    }
    
    b->in=b->out=b->start=NULL;

    while((red = readln(b, &buf)) > 0)
        write(1, buf, red);

    destroy_buffer(b);
    free(b);
    exit(0);
}

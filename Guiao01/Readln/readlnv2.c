#include "readlnv2.h"

ssize_t readln(struct buffer_t *b, void **buf){

    ssize_t res = -1;

    if(b->out){
        *buf = b->out->st;
        b->out = b->out->next;
        res = strlen(*buf);
    }
    else{
        if((res=create_buffer(0, b, BLOCKSIZE)) > 0){
            *buf = b->out->st;
            b->out = b->out->next;
            res = strlen(*buf);
        }            
    }
        
    return res;
}


int create_buffer(int fildes, struct buffer_t *b, size_t nbyte){


    int len, i;
    ssize_t res;
    char *buf = (char*)malloc(sizeof(char)*nbyte);

    if(!buf) fprintf(stderr, "Not enough space to meet request\n");
    
    res = read(fildes, buf, nbyte);
        
    if(res <= 0) return -1;

    destroy_buffer(b);

    for(i = 0, len = 0; i < res; i ++, len = 0){

        if(b->in){
                b->in->next = (Elem)malloc(sizeof(struct elem));
                b->in = b->in->next;
        }else{
                b->in = (Elem)malloc(sizeof(struct elem));
                b->out = b->in;
                b->start = b->in;
        }

        

        while(i < res && buf[i] != '\n'){ 
            len ++;
            i ++;
        }

        b->in->st = strndup(&(buf[i-len]), len+1);
        b->in->next = NULL;

    }
    
    free(buf);

    return 1;

}

int destroy_buffer(struct buffer_t *b){

    Elem aux;

    if(b){
        while(b->start){
            aux = b->start->next;
            free(b->start->st);
            free(b->start);
            b->start = aux;
        }
        b->start = b->in = b-> out = NULL;
    }
}
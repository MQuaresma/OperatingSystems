#include "readlnv3.h"

size_t readln(struct buffer_t *b, void **buf){

    ssize_t res=-1, block = 1024;
    char *s = (char*)malloc(sizeof(char)*block);
    

    if(b->in != b->out){
        *buf = b->buf[b->out ++];
         res = strlen(*buf);
    }

    else{
        res = read(0, s, block-1);

        if(res>0){
            s[res] = '\0';
            *buf = s;
            if(res<block-1)
                create_buffer(0, b, block-res);
        }

    }

    return res;
}


int create_buffer(int fildes, struct buffer_t *b, size_t nbyte){

    char *temp = (char*)malloc(sizeof(char)*nbyte);
    ssize_t res, tot=0;
    int inS = b->in;

    while((res = read(fildes, temp, nbyte))>0 && tot < nbyte){
        tot += res;
        temp[res] = '\0';
        b->buf[b->in] = temp;
        b->in ++;
        temp = (char*)malloc(sizeof(char)*nbyte);
    }
    return b->in - inS;
}

    
/*int destroy_buffer(struct buffer_t *buffer){




}*/


main(){

    char **in;
    ssize_t res;
    struct buffer_t b;

    b.in = b.out = 0;

    while((res=readln(&b, in))>0){
        write(1, *in, res);
        free(*in);
    }

}

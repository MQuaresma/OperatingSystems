#include "readln.h"


ssize_t readln(int, void*, size_t);
size_t parse(char*);

int main(int argc, char *argv[]){

    size_t blockSize=1, red;
    char *block;
    
    if(argc <=1 ){
        fprintf(stderr, "Not enought arguments provided\n");
        exit(1);
    }

    else if(isdigit(**++argv)) blockSize = parse(*argv);
    
    block = (char*)malloc(sizeof(char)*(blockSize));

    if(!block){
        fprintf(stderr, "Not enought space\n");
        exit(1);
    }

    while((red=readln(0, block, blockSize))>0)
        write(1, block, red); 

    exit(0);    
}


size_t parse(char *targ){

    size_t blockS=0;
     
    while(*targ && isdigit(*targ)){
        blockS = blockS*10+(*targ++-'0'); 
    }
    return blockS;
}

/* reads until a new line char is found or until block is reached */
ssize_t readln(int fildes, void *buf, size_t block){

    ssize_t i, r;
    char *st=buf;

    for(i = 0; i < block && (r=read(fildes, st+i, 1)) > 0 && *(st+i) != '\n'; i ++);

    if(*(st+i) == '\n') i ++;

    return i;
}

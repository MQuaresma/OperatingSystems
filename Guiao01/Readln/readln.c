#include "readln.h"


int main(int argc, char *argv[]){

    size_t blockSize=1;
    ssize_t red, temp;
    char *block;
    
    if(argc <=1 ){
        fprintf(stderr, "Block size specified\n");
        exit(1);
    }

    else if(isdigit(**++argv)) blockSize = atoi(*argv);
    
    block = (char*)malloc(sizeof(char)*(blockSize));

    if(!block){
        fprintf(stderr, "Not enought space\n");
        exit(1);
    }

    while((red=readln(0, block, blockSize))>0){
        while(red == blockSize+1){
            block = (char*)realloc(block, sizeof(char)*blockSize*2);
            if(!block){
                fprintf(stderr, "Not enough space\n");
                exit(1);
            }
            else{
                blockSize *= 2;
                if((temp = readln(0, block+red, blockSize-red)) <= 0) exit(1);
		        red = red+temp;	
            }
        } 
        write(1, block, red);
    }

    exit(0);    
}

/* reads until a new line char is found or until block is reached */
ssize_t readln(int fildes, void *buf, size_t block){

    ssize_t i, r;
    char *st = buf;

    for(i = 0; i < block && (r=read(fildes, st+i, 1)) > 0 && *(st+i)!= '\n'; i ++);

    if(*(st+i) == '\n') i ++;

    return i+((i >= block)? 1 : 0);
}
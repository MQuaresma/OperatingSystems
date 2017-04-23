#include "nl-v1.h"

/* reads until a new line char is found or until block is reached */
ssize_t readln(int fildes, void *buf, size_t block){

    ssize_t i, r;
    char *st=buf;

    for(i = 0; i < block && (r=read(fildes, st+i, 1)) > 0 && *(st+i) != '\n'; i ++);

    if(*(st+i) == '\n') i ++;
    *(st+i) = '\0';

    return i;
}

void itoa(int in, char p[]){
    
    int i=0;

    do{
        p[i++] = (in%10) + '0';
    }while(in/=10);

    p[i] = '\0';

    reverse(p, i);
}

void reverse(char p[], int size){

    char c;
    int j=0;

    while(j < --size){
        c = p[size];  
        p[size] = p[j];
        p[j++] = c;
    }

}
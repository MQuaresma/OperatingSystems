#include "guiao01.h"
#define SIZE 10

ssize_t readln(int, void*, size_t);
void itoa(int, char*);

int main(int argc, char *argv[]){

    size_t block = 100, r;
    int fildes=0, line = 1, m;
    char *buf=(char*)malloc(sizeof(char)*block);
    char no[SIZE];

    if(--argc > 0){
        ++ argv;
        fildes = open(*argv, O_RDONLY);

        if(fildes < 0){
            fprintf(stderr, "File (%s) not found\n", *argv);
            exit(1);
        }
        else printf("\t\n-------File: %s------\n",*argv);
    }

    no[0] = '\t';
    while((r = readln(fildes, buf, block))>0){
        //sprintf(no+1, "%d", line++); //could also use sprintf to parse the integer to a string
        itoa(line++, no+1);
        write(1, no, strlen(no));
        write(1, buf, r);
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

void reverse(char p[], int size){

    char c;
    int j=0;

    while(j < --size){
        c = p[size];  
        p[size] = p[j];
        p[j++] = c;
    }

}

void itoa(int in, char p[]){
    
    int i=0;

    do{
        p[i++] = (in%10) + '0';
    }while(in/=10);

    p[i] = '\0';

    reverse(p, i);
}

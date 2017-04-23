#include "nl-v1.h"

int main(int argc, char *argv[]){

    size_t block = 100, r, temp;
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
        while(r == block+1){
            buf = (char*)realloc(buf, sizeof(char)*block*2);
            if(!block){
                fprintf(stderr, "Not enough space\n");
                exit(1);
            }
            else{
                block *= 2;
                if((temp = readln(0, buf+r, block-r)) <= 0) exit(1);
		        r = r+temp;	
            }
        }
        write(1, no, strlen(no));
        write(1, buf, r);
    }    
}
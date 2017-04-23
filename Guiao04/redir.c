#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <fcntl.h>
#define IN "-i"
#define OUT "-o"

int main(int argc, char *argv[]){

    int fI, fO;

    if(!--argc){
        perror("No arguments provided\n");
        exit(1);
    }

    while(--argc){
        ++argv;
        if(!strcmp(*argv, IN)){
            ++ argv;
            --argc;
            fI = open(*argv, O_RDONLY, 0644);
            if(fI < 0){
                perror("File not found\n");
                exit(1);
            }
            dup2(fI, 0);       //mapeia o stdin para fI 
            close(fI);
        }else if(!strcmp(*argv, OUT)){
            ++ argv;
            --argc;
            fO = open(*argv, O_WRONLY|O_CREAT, 0644);
            dup2(fO, 1);      //mapeia o stdout para fI 
            close(fO);
        }else execvp(*argv, argv);
    }    
    
}

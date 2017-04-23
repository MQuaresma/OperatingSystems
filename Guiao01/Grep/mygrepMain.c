#include "mygrep.h"


main(int argc, char *argv[]){

    int fildes = 0;
    char *pattern;

    if(argc < 2){
        fprintf(stderr, "No pattern provided\n");
        exit(1);
    }
    argc -= 2;
    pattern = *++argv; 
    while(argc -- > 0){
        ++argv;
        fildes = open(*argv, O_RDONLY)

        
    }

}
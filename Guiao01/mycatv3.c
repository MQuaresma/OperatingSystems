#include "guiao01.h"

/*
 * mycatv3: programa semelhante ao cat que lê a partir de um ficheiro
 * especificado como parâmetro,
 * em blocos de n bytes, sendo n passado como argumento,
 * e processa os dados, fazendo o seu output de seguida, tudo num 
 * unico ciclo
 */
int main(int argc, char *argv[]){

    size_t byteBlock=2048, red;
    char c;
    int fildes = 0;
    char *block;

    if(argc <= 1){
        fprintf(stderr, "Not enough arguments provided\n");
        exit(1);
    }

    block = (char*)malloc(sizeof(char)*byteBlock);
    if(!block){
        fprintf(stderr, "Block size too big, terminating...\n");
        exit(1);
    }

    ++argv;
    --argc;

    while(argc){
        fildes = open(*argv, O_RDONLY);
        if(fildes > 0){
            printf("\n-----File:%s------\n", *argv);
            while((red=read(fildes, block, byteBlock)) > 0)
                write(1, block, red);
        }
        else printf("\n-------File (%s) not found-------\n", *argv);
        argc --;
        ++argv; 
    }

    exit(0);

}

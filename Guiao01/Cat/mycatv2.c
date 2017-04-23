#include "mycat.h"

/*
 * mycatv2: programa semelhante ao cat mas que apenas lê do standard input,
 * em blocos de n bytes, sendo n passado como argumento,
 * e processa os dados, fazendo o seu output de seguida, tudo num 
 * unico ciclo
 */
int main(int argc, char *argv[]){

    ssize_t byteBlock=0, red;
    char c;
    char *block;

    if(argc <= 1){
        fprintf(stderr, "Not enough arguments provided\n");
        exit(1);
    }
    ++argv; 
    while(**argv && isdigit(**argv)){
        byteBlock = (byteBlock*10) + (**argv-'0');
        ++*argv;
    }

    block = (char*)malloc(sizeof(char)*(byteBlock+1));
    if(!block){
        fprintf(stderr, "Block size too big, terminating...\n");
        exit(1);
    }


    while((red=read(0, block, byteBlock)) > 0){
        block[red] = '\0'; /* read doesn't add the null character at the end */
        write(1, block, red);
    }
     

    exit(0);

}

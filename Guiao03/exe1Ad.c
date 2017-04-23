#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

void parseCmd(char *cmd, char *argv[]){

    int i = 0;
    
    *(argv+i) = strtok(cmd, " ");
    
    while(argv[i++])
        argv[i] = strtok(NULL, " ");
    
}


void mySystem(char *cmd){

    int i, len, code, eCode=0;

    for(i = 0, len = 0; cmd[i]; len += (cmd[i] == ' '), i ++);

    char *argv[len];

    parseCmd(cmd, argv);

    do{
        eCode ++;
        if(!fork()){
            execvp(*argv, argv);
            perror("execvp");
            _exit(0);
        }
        wait(&code);
    }while(WEXITSTATUS(code) > 0);

    exit(eCode);
}

/*
 * Corre programas fornecidos como argumentos até que o seu código de saída seja 0
 * Imprime o nro de vezes que cada um foi executado.
 */
int main(int argc, char *argv[]){

    int code, pid[argc-1];


    for(int i = 1; i < argc; i ++)
        if(!(pid[i] = fork())) mySystem(argv[i]);

    for(int i = 1; i < argc; i ++){
        waitpid(pid[i], &code, 0);
        printf("%s %d\n", argv[i], WEXITSTATUS(code));
    }    

}

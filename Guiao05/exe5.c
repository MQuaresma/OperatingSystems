#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 4

char **parse(char *);

int main(int argc, char *argv[]){

    int ant, dp[2];
    char **args;

    ++argv;
    --argc;

    for(int i = 0; i < argc; i ++){
        pipe(dp);
        if(!fork()){
            args = parse(argv[i]); 
            if(!i){ 
                close(dp[0]);           //nao e necessario o output do pipe
                if(argc > 1) dup2(dp[1], 1);         //direcionar output do programa para o input do pipe
            }
            else if(i == argc-1){ 
                dup2(ant, 0);
                close(ant);
                close(dp[0]);
            }else{
                dup2(ant, 0);
                close(ant);
                dup2(dp[1], 1);
            }
            close(dp[1]);
            execvp(args[0], args); 
            perror(args[0]);            //se esta instruçao for executado ocorreu um erro
        }
        wait(0L);
        if(i!=argc-1)close(dp[1]);
        if(i) close(ant);
        ant = dp[0];
    }
    
}


char **parse(char *cmd){

    int i, argc;
    char **argv;

    for(i = 0, argc = 1; cmd[i]; argc += (cmd[i] == ' ') , i ++);

    argv=(char**)malloc(sizeof(void*)*argc);

    i = 0;
    argv[i] = strtok(cmd, " \t\n");
    while(argv[i++]) argv[i] = strtok(NULL, " \t\n");

    return argv;
}

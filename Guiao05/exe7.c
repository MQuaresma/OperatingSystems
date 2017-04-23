#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/wait.h>
#define SIZE 512
#define IN "<"
#define OUT ">"
#define OUTA ">>"
#define ERR "2>"
#define ERRA "2>>"
#define PIPE "|"

/*
 * Interpretador de comandos similar a bash. 
 * Suporta redireccinamento de I/O sob a forma de
 * operadores de redireccionamento bem como de 
 * pipes anonimos.
 */

void settings(char **argv, int len, int *rib);
char **scanCommand(char cmd[], int *rib, int *end);
int redirIO(char **argv, int len, int *rib, int *redir);

void mySystem(char *cmdV[], int rib, int len){

    char *argv[len+1];

    for(int i = 0; i < len; i ++) argv[i] = cmdV[i];

    argv[len] = NULL;

    execvp(*argv, argv);
    perror("execvp");
    exit(-1);

}

char **commands(char cmd[], int *nC){
    
    int len, i;
    char **argv;

    for(i = 0, len = 1; cmd[i]; len += (cmd[i] == '|'), i ++);

    *nC = len;
    argv = (char**)malloc(sizeof(void*)*len);

    if(argv){
        i = 0;
        argv[i] = strtok(cmd, PIPE);
        while(argv[i]) argv[++i] = strtok(NULL, PIPE);
    }

    return argv;
}

void execCommands(char **argv, int len){

    char **aux = NULL;
    int pd[2], rib, end, in;

    for(int i = 0; i < len; i ++){
        pipe(pd);
        if(!fork()){
            aux = scanCommand(argv[i], &rib, &end);
            if(!i && len > 1){ 
                dup2(pd[1], 1);     //direcionar output do programa para o input do pipe 
            }else if(len > 1){
                dup2(in, 0);
                close(in);
                if(i != len-1 && len > 1) dup2(pd[1], 1);
            }
            close(pd[1]);         
            close(pd[0]);
            mySystem(aux, rib, end);
        }
        if(len > 1 || !rib) wait(NULL);     //wait if there's no pipe or if it's not supposed to run in the background
        if(i) close(in);
        in = pd[0];
        close(pd[1]); 
    }
    close(pd[0]);
}


char **scanCommand(char cmd[], int *rib, int *end){

    int len, i, redir = 0;
    char **argv;
 
    for(i = 0, len = 0; cmd[i];){
        while(cmd[i] && cmd[i] == ' ') i ++;
        len += (cmd[i] && cmd[i] != ' ');
        while(cmd[i] && cmd[i] != ' ') i ++;
    }

    i = 0;
    argv = (char**)malloc(sizeof(void*)*len);
    argv[i] = strtok(cmd, " ");
    while(argv[i])
        argv[++i] = strtok(NULL, " ");    

    *end = redirIO(argv, len, rib, &redir);
    if(!redir) *end = len;
    return argv;
}

int redirIO(char **argv, int len, int *rib, int *redir){

    int fT, fst=-1;
    char *aux;

    for(int i = 0; i < len; i ++){
        if(!strcmp(argv[i], IN)){ 
            if(fst == -1) fst = i;
            fT = open(argv[++i], O_RDONLY);
            dup2(fT, 0);
            close(fT);
        }else if(!strcmp(argv[i], ERRA)){ 
            if(fst == -1) fst = i;
            fT = open(argv[++i], O_APPEND | O_WRONLY | O_CREAT);
            dup2(fT, 2);
            close(fT);
        }else if(!strcmp(argv[i], OUTA)){ 
            if(fst == -1) fst = i;
            fT = open(argv[++i], O_APPEND | O_WRONLY | O_CREAT);
            dup2(fT, 1);
            close(fT);
        }else if(!strcmp(argv[i], ERR)){ 
            if(fst == -1) fst = i;
            fT = open(argv[++i], O_WRONLY | O_CREAT);
            dup2(fT, 2);
            close(fT);
        }else if(!strcmp(argv[i], OUT)){ 
            if(fst == -1) fst = i;
            fT = open(argv[++i], O_WRONLY | O_CREAT);
            dup2(fT, 1);
            close(fT);
        }else if((aux = strstr(argv[i], "&"))){ 
            *rib = 1;
            *aux = 0; //remove character
        }
    }

    *redir = (fst != -1);

    return fst;
}

int main(){

    char cmd[SIZE], **argv;
    ssize_t r = 1;
    int exit = 0, c;

    while(!exit && r > 0){
        r = read(0, cmd, SIZE-1);
        if(r > 0){
            exit = !strncmp(cmd, "exit", 4);
            if(!exit){           
                cmd[r-1] = 0;
                argv = commands(cmd, &c);           //split the line into its commands
                execCommands(argv, c);
                free(argv);
            }
        }    
    }
}

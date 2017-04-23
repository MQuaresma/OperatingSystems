#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/wait.h>
#define IN "<"
#define OUT ">"
#define OUTA ">>"
#define ERR "2>"
#define ERRA "2>>"


void settings(char **argv, int len, int *rib);

int mySystem(char *cmd, int rIB){
    int i, len, code;

    for(i = 0, len = 0; cmd[i]; len += (cmd[i] == ' '), i ++);

    char *argv[len];
    i = 0;

    *(argv+i) = strtok(cmd, " ");
    
    while(argv[i++])
        argv[i] = strtok(NULL, " ");
    
    if(!fork()){
        execvp(*argv, argv);
        perror("execvp");
        exit(-1);
    }

    if(rIB)wait(&code);

    return code;  
}

void scanCommand(char cmd[], int *rib){

    int fT, len, i, err;
    char **argv;
 
    for(i = 0, len = 0; cmd[i]; len += isspace(cmd[i]), i ++);
    
    i = 0;
    argv = (char**)malloc(sizeof(void*)*len);
    argv[i] = strtok(cmd, " ");
    while(argv[i++])
        argv[i] = strtok(NULL, " ");    
        
    settings(argv, len, rib);
    free(argv);
}

void settings(char **argv, int len, int *rib){

    int fT;

    for(int i = 0; i < len; i ++){
        if(!strcmp(argv[i], IN)){ 
            fT = open(argv[++i], O_RDONLY);
            dup2(fT, 0);
            close(fT);
        }
        else if(!strcmp(argv[i], ERRA)){ 
            fT = open(argv[++i], 'a');
            dup2(fT, 2);
            close(fT);
        }
        else if(!strcmp(argv[i], OUTA)){ 
            fT = open(argv[++i], 'a');
            dup2(fT, 1);
            close(fT);
        }
        else if(!strcmp(argv[i], ERR)){ 
            fT = open(argv[++i], O_WRONLY | O_CREAT);
            dup2(fT, 2);
            close(fT);
        }
        else if(!strcmp(argv[i], OUT)){ 
            fT = open(argv[++i], O_WRONLY | O_CREAT);
            dup2(fT, 1);
            close(fT);
        }
        else if(strstr(argv[i], "&")) *rib = 1;
    }

}

int main(){

    char cmd[100];
    ssize_t r = 1;
    int exit = 0, rib;

    while(!exit && r > 0){
        r = read(0, cmd, 100-1);
        if(r > 0){
            exit = !strncmp(cmd, "exit", 4);
            if(!exit){           
                cmd[r] = 0;
                if(!fork()){ 
                    scanCommand(cmd, &rib);
                    mySystem(cmd, rib);
                }
            }
        }    
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <wait.h>


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

int main(){

    char cmd[100];
    ssize_t r = 1;
    int exit = 0, rIB;

    while(!exit && r > 0){
        r = read(0, cmd, 100);
        if(r > 0){
            exit = !strncmp(cmd, "exit", 4);
            if(!exit){
                    rIB = cmd[r-2] == '&';             
                    cmd[r-1-(rIB == 1)] = 0;
                    mySystem(cmd, rIB);
            }
        }    
    }
}

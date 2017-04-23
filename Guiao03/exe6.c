#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>


int mySystem(char *cmd){

    int i, len, code;

    for(i = 0, len = 0; cmd[i]; len += (cmd[i] == ' '), i ++);

    char *argv[len];
    i = 0;

    *(argv+i) = strtok(cmd, " ");
    
    while(argv[i++])
        argv[i] = strtok(NULL, " ");
    
    if(!fork()){
        execvp(*argv, argv);
        exit(-1);
    }

    wait(&code);

    return code;  

}

int main(int argc, char *argv[]){

    return WEXITSTATUS(mySystem(*++argv));

}

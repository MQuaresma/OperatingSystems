#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

//store child's pid and command in a dict style array
//set signal handlers for SIGALRM and SIGCHLD


int main(int argc, char *argv[]){

    int i = 1, x[argc-1]={0};
    signal(SIGALRM, action);
    signal(SIGCHLD, action);
    
    while(1){
        execlp(argv[i], argv[i], NULL);
        pause(); 
    }

}


void executeCommands(int sig){

    static int i = 1;
    static int x[agc];
    static int firstRun = 1;

    if(i >= agc) i = 1;

    alarm(1);
    switch(sig){
        case SIGALRM:
            kill(*prev, SIGSTOP);
            if(!firstRun) kill(x[i], SIGCONT);
            else 
            break;
        case SIGCHLD:
            if(i == argc-1) i = 1;
            else i ++;
            break;
    }

}

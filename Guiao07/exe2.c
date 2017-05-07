#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#define TIMER 1

//store child's pid and command in a dict style array
//set signal handlers for SIGALRM and SIGCHLD

static int *cur;

void alarmHandler(int sig){

    kill(*cur, SIGSTOP); //pause child

}

void chldManager(int sig){

    *cur = 0; //child has finished

}


int main(int argc, char *argv[]){

    int *x;
    signal(SIGALRM, alarmHandler);
    signal(SIGCHLD, chldManager);

    if(argc >= 1){
        x = (int*)calloc(argc-1, sizeof(int));
        while(1){
            for(int i = 1; i < argc; i ++){
                cur = x+i-1;
                alarm(TIMER);
                if(!(*cur) && !(x[i-1] = fork())) execlp(argv[i], argv[i], NULL);
                else kill(*cur, SIGCONT);
                pause();
            }    
        }
        free(x);
    }    
    
}

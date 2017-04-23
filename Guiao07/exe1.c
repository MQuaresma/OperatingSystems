#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#define TT 10000

void actions(int sig);

main(){

    sig_t pd = (void (*)(int))actions;
    alarm(TT);           //definir alarme que corre indefinidamente
    signal(SIGINT, pd);
    signal(SIGQUIT, pd);
    signal(SIGALRM, pd);
    
    while(1) pause();

}


void actions(int sig){
    
    static int times = 0;
    static long elapsed = 0;

    if(sig == SIGINT){
        times ++;
        elapsed += TT-alarm(TT);
        printf("Elapsed Time: %ld\n", elapsed); 
    }else if(sig == SIGALRM){
        alarm(TT);
    }else{
        printf("Times pressed Ctrl-C: %d\n", times);
        exit(0);
    }
}

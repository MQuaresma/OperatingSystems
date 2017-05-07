#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#define TT 10000

void actions(int sig);

main(){

    signal(SIGINT, actions);
    signal(SIGQUIT, actions);
    signal(SIGALRM, actions);
    alarm(TT);           //definir alarme que corre indefinidamente
        
    while(1) pause();

}


void actions(int sig){
    
    static int times = 0;
    static unsigned long elapsed = 0;

    switch(sig){
        case SIGINT:
            times ++;
            signal(SIGALRM, SIG_IGN);      //ignore expiring timers
            signal(SIGINT, SIG_IGN);      //ignore expiring timers
            elapsed += (TT-alarm(TT));
            printf("Elapsed Time: %lu\n", elapsed); 
            signal(SIGALRM, actions);
            signal(SIGINT, actions);
            break;
        case SIGALRM:
            elapsed += TT;
            alarm(TT);
            break;
        default:
            printf("Times pressed Ctrl-C: %d\n", times);
            exit(0);
    }
    
}

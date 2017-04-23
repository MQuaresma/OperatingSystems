#include <stdio.h>
#include <unistd.h>

int main(){

    int pd[2];

    pipe(pd);

    if(!fork()){
        close(pd[0]);
        dup2(pd[1], 1);
        close(pd[1]);
        execlp("ls", "ls", "/sbin", NULL);  
        perror("ls");
        _exit(1); 
    }
    if(!fork()){
        close(pd[1]);
        dup2(pd[0], 0);
        close(pd[0]);
        execlp("wc", "wc", "-l", NULL);  
        perror("wc");
        _exit(1); 
    }else{
        close(pd[0]);
        close(pd[1]);
    }

}

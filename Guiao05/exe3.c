#include <stdio.h>
#include <unistd.h>

int main(){

    int pd[2], in;
    char buf[100];

    pipe(pd);

    if(!fork()){

        close(pd[1]);
        dup2(pd[0], 0);
        close(pd[0]);

        execlp("wc", "wc", "-w", NULL);
        perror("wc");
        _exit(1);

    }else{
        close(pd[0]);
        in = read(0, buf, 100);
        write(pd[1], buf, in);
        close(pd[1]);
    }

}

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>


/*
 * Exemplo de comunicaçao de dados entre
 * pai e filho através de pipes
 */
int main(){

    int pd[2], n, dados[1024];
    char buf;

    pipe(pd); //cada posiçao do array ficara com um file descriptor de onde se pode ler e escrever

    if(!fork()){    //filho escreve nos pipes
        close(pd[0]);

        dup2(pd[1], 1);
        close(pd[1]);

        execlp("ls", "ls", NULL);
        perror("ls");
        _exit(1);

    }else{          //pai le dos pipes

        close(pd[1]);                   //escrever para um pipe onde nao esta ngm a ouvir mata o processo que tentou escrever
        while(read(pd[0], &buf, 1) > 0)
            printf("%c", toupper(buf));

    }    

}

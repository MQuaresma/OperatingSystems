#include <stdio.h>
#include <unistd.h>


/*
 * Exemplo de comunicaçao de dados entre
 * pai e filho através de pipes
 */
int main(){

    int pd[2];
    char buf[10];

    pipe(pd); //cada posiçao do array ficara com um file descriptor de onde se pode ler e escrever

    if(!fork()){    //filho escreve nos pipes
        write(pd[1], "ab", 2);
        write(pd[1], "cde", 3);
    }else{          //pai le dos pipes
        read(pd[0], buf, 3);
        read(pd[0], buf, 2);
        printf("%c\n", *buf);
    }    

}

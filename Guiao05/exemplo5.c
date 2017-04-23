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

        close(pd[0]);
        sleep(5);
        write(pd[1], "ab", 2);
        write(pd[1], "cde", 3);
    }else{          //pai le dos pipes

        close(pd[1]);
        while(read(pd[0], buf, 1) > 0) //leitura de um pipe vazio provoca a espera do programa que esta a tentar ler do mesmo
            printf("%c\n", *buf);
    }    

}

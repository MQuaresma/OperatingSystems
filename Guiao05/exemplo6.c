#include <stdio.h>
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

        for(int i = 0; i < 10000; i ++){
            n = write(pd[1], dados, 1024);
            printf("Escrevi %d bytes, i = %d\n", n, i);
        }    

    }else{          //pai le dos pipes

        close(pd[1]);
        
        while(read(pd[0], &buf, 1) > 0){ //leitura de um pipe vazio provoca a espera do programa que esta a tentar ler do mesmo
            printf("%c\n", buf);
            sleep(1);
        }    
    }    

}

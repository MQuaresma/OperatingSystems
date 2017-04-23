#include <sys/unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10000

/*
*	exemplo da utilizaçao do system call fork
*	para criaçao de processos paralelos;
*	procura de nro de ocorrencias 
*	de elemento numa matriz
*/

main(){

	int m[5][N];
	int i, j, cont=0, k;
	pid_t x;

	for(i = 0; i < 5; i ++){
		x = fork();				/* criaçao de processo filho; ponto e virgula ja executado pelo pai e filho */
		wait(0L);
		if(!x){					/* x  e o unico dado que difere entre pai/filho, o resto das variaveis sao iguais, mas nao partilhadas */
			for(j = 0; j < N; j ++)
				if(m[i][j] == k) cont ++;
			printf("%d\n", cont);
			exit(0);				/* impede o filho de continuar a percorrer as linhas que nao lhe dizem respeito */
		}
	}
}
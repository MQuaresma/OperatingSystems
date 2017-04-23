#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 100000

void genMatrix(int [][N], int);


int main(int argc, char *argv[]){


	int mt[10][N], code, found, k, j, i;

	if(--argc>0) k=atoi(*++argv);
	else return 1;

	genMatrix(mt, 10);

	for(i = 0; i < 10; i ++){
		if(!fork()){
			for(j = 0; j < N && mt[i][j] != k; j ++);
			_exit(j<N);
		}
	}

	for(i = 0, found = 0; i < 10 && !found; i ++){
        wait(&code);
		found = WEXITSTATUS(code);
	}

	printf((found ? "Found\n" : "Not found\n"));

}


void genMatrix(int mt[][N], int l){

	for(int i = 0; i < l; i ++)
		for(int j = 0; j < N; j ++)
			mt[i][j] = (j*i)%N;
}

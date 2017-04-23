#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 100000

void genMatrix(int [][N], int);


int main(int argc, char *argv[]){


	int mt[10][N], code, found = 0, k, j;
	int x[10]={0};

	if(--argc>0) k=atoi(*++argv);
	else return 1;

	genMatrix(mt, 10);

	for(int i = 0; i < 10; i ++){
		x[i] = fork();
		if(!x[i]){
			for(j = 0; j < N && mt[i][j] != k; j ++);
			_exit(j<N);
		}
	}

	for(int i = 0; i < 10; i ++){
		waitpid(x[i], &code, 0);
		found = WEXITSTATUS(code);
        if(found) printf("Line %d\n", i);
    }

}


void genMatrix(int mt[][N], int l){

	for(int i = 0; i < l; i ++)
		for(int j = 0; j < N; j ++)
			mt[i][j] = (j*i)%N;
}

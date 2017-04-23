#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 10


main(){

	int x[N]={0}, code;

	for(int i = 0; i < N; i ++){
		x[i] = fork();
		if(!x[i]) _exit(i);
	}

	for(int i = 0; i < N; i ++){
		waitpid(x[i], &code, 0);
 		printf("%d\n", WEXITSTATUS(code));	
	}


}

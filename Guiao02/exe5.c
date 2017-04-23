#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 10


/*
* Create ten childs of depth and each child prints 
* its PID and its parent's PID
*/
main(){

	int i;
	pid_t x=0;

	for(i = 0; i < N && !x; i ++){
		printf("My PID: %d\nParent PID: %d\n", getpid(), getppid());
		if(!x){
			x = fork();
			wait(NULL);
		}
	}

}

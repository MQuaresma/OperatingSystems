#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

main(){

	pid_t x;
	int code;

	for(int i = 1; i < 10; i ++){
		x = fork();
		wait(&code);
		if(!x) printf("My PID: %d\nParent PID: %d\n", getpid(), getppid()), _exit(i);
		printf("Exit Code: %d\n", WEXITSTATUS(code));
	}



}

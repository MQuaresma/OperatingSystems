#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

main(){

	pid_t x;

	x = fork();
	
	printf("My PID: %d\n", getpid());

	if(!x) printf("Parent PID: %d\n", getppid());
	else printf("Son PID: %d\n", x);
	
}
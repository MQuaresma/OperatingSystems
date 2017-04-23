#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

main(){

	printf("Pid: %d\n", getpid());
	printf("Parent pid: %d\n", getppid());

}
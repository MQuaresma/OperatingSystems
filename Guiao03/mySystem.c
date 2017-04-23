#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int mySystem(char *cmd){

	int code, i, argc;

	for(i = 0, argc = 1; cmd[i]; argc += (cmd[i] == ' '), i ++);

	char *argv[argc];

	argv[i=0] = strtok(cmd, " \t\n");
	
	while(argv[i])
		argv[++i] = strtok(NULL, " \t\n");
	
	if(!fork()){
		execvp(argv[0], argv);
		_exit(1);
	}

	wait(&code);
	return WEXITSTATUS(code);

}

main(int argc, char *argv[]){

	int code;
	
	if(--argc>0) code = mySystem(*++argv);

	return code;
}

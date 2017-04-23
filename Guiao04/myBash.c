#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define LINE 1000

void executeC(char *cmd, int bg){

	int i, len;

	for(i = 0, len = 0; cmd[i]; len += (cmd[i] == ' '), i ++); 

	char *argv[len];
	i = 0;

	argv[i] = strtok(cmd, " \t\n");
	while(argv[i++]) argv[i] = strtok(NULL, " \t\n");

	if(!fork())
		execvp(argv[0], argv);
	if(bg) wait(0L);

}



int main(){

	char command[1000];
	ssize_t r;
	int end = 0, bg, fI, fO, fE;

	while(!end && (r = read(0, command, LINE)) > 0){
		end = !strncmp(command, "exit", r-1);
		command[r] = '\0';
		bg = (command[r-1] != '&'); 
		if(!end) executeC(command, bg);
	}
}

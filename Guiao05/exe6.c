#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/*
 * Implementation of the popen function but instead it returns a 
 * file descriptor as opposed to a pointer to FILE
 */

char **processCmd(char *cmd){

    char **argv;
    int len, i;

    for(i = 0, len = 1; cmd[i]; len += isspace(cmd[i]), i++);

    argv = (char**)malloc(sizeof(void*)*len);

    argv[(i=0)] = strtok(cmd, " ");

    while(argv[i++]) argv[i] = strtok(NULL, " ");

    return argv;

}

int mypopen(char *cmd, char mode){

    int pd[2], m;
    char **argv;

    pipe(pd);
    argv = processCmd(cmd);


    m = (mode == 'r');
    
    if(!fork()){
        close(pd[!m]);          //close unecessary file descriptors
        dup2(pd[m], m);
        close(pd[m]);
        execvp(argv[0], argv);
    }

    close(pd[m]);
    //if i was to return a pointer to a FILE the function fdopen would convert a file descriptor to a FILE*
    return pd[!m];

}


main(int argc, char *argv[]){

    ssize_t r;
    int interface;
    char buf[1000];
        
    interface = mypopen(argv[1], argv[2][0]);

    if(argv[2][0] == 'w') write(interface, "hello", 5);
    else{ 
        r = read(interface, buf, 1000);
        if(r > 0) write(1, buf, r);
    }

}

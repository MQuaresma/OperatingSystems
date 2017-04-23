#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define LINE 1000


int main(int argc, char *argv[]){

    int in = open("/etc/passwd", 640), out = open("saida.txt", O_CREAT | O_WRONLY), err = open("erros.txt",  O_CREAT | O_WRONLY);
    char line[LINE];
    ssize_t rd;

    dup2(in, 0);
    close(in);
    dup2(out, 1);
    close(out);
    dup2(err, 2);
    close(err);

    if(!fork()){
        rd = read(0, line, LINE);
        execlp("wc", "wc", NULL);
        perror("execlp:");                   //an error ocurred since the exec didn't succeed
    }    
    wait(0L);
}

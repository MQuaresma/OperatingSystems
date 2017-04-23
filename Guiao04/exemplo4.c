#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

    printf("Antes\n");
    char buf[100];

    int fd = open("teste.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    dup2(fd, 0);  
    close(fd);              //como o 0(stdin) esta associado ao fd também vai ser fechado

    printf("Depois\n");

    fgets(buf, 100, stdin);
    printf("Li: %s\n", buf);

}

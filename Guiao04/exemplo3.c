#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

main(){

    printf("Antes\n");

    int fd = open("teste.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);

    dup2(fd, 1);   //todas as referencias a um dos dois descritores apontam para o msm ficheiro

    fork();

    printf("Depois\n"); //como o file descriptor 1 esta associado ao stdout esta escrita sera no ficheiro teste

}

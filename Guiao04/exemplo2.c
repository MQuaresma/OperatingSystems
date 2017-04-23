#include <stdio.h>
#include <sys/unistd.h>
#include <fcntl.h>

main(){

    printf("Antes\n");

    int fd = open("teste.txt", O_WRONLY|O_CREAT, 0644);
    write(fd, "ola\n", 4);

    dup2d(fd, 1);

    printf("Depois\n");
    
    close(fd);

}

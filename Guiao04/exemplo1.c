#include <stdio.h>
#include <sys/unistd.h>
#include <fcntl.h>

main(){

    printf("Antes\n");

    int fd = open("teste.txt", O_RDONLY | O_CREAT, 0644);
    write(fd, "ola\n", 4);

    printf("Depois\n");
    
    close(fd);

}

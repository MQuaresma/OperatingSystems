#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


main(){

    char buf[100];
    ssize_t r;
    int fd;

    if(mkfifo("fifo", 0777) >= 0){
        fd = open("fifo", O_RDONLY);
        if(fd > 0){
            while((r = read(fd, buf, 100))>0)
                write(1, buf, r);
            close(fd);
        }
    }else perror("mkfifo: ");

}

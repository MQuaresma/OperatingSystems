#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

    int fd = open("pipe", O_WRONLY); 
    
    if(fd > 0){
        ++argv;
        write(fd, *argv, strlen(*argv));
        close(fd);
    }

}
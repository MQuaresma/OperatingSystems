#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

main(){

    char buf[1000];
    ssize_t r;
    int lg = open("log", O_WRONLY | O_CREAT), pp;
    
    if(lg < 0) perror("open: "); 
    else if(mkfifo("pipe", 0666) >= 0){
        pp = open("pipe", O_RDONLY);
        if(pp > 0){
            while((r = read(pp, buf, 1000))>=0) 
                write(lg, buf, r);
            close(lg);
        }
    }else perror("mkfifo: ");

}

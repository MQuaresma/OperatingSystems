#include <unistd.h>

/* parent process sends/recieves info through the pipe */
main(){

    char buf[100];
    int pd[2];  //each position stores a file descriptor for the I/O of the pipe
    
    pipe(pd);

    if(!fork()){
        close(pd[1]);
        ssize_t r = read(pd[0], buf, 100);  //child blocks while parent is sleeping
        if(r > 0) write(1, buf, r);
    }else{
        close(pd[0]);
        sleep(5);   //parent sleeps for 5 seconds
        write(pd[1], "Hello, this is the parent process\n", 34);
    }

}
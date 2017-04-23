#include <unistd.h>

/* parent process sends/recieves info through the pipe */
main(){

    char buf[100];
    ssize_t r;
    int pd[2];  //each position stores a file descriptor for the I/O of the pipe
    
    pipe(pd);

    if(!fork()){
        close(pd[1]);
        while((r = read(pd[0], buf, 100)) >= 0)  //read while there is someone transmiting
            write(1, buf, r);
    }else{
        close(pd[0]);
        write(pd[1], "Hello, this is the parent process\n", 34);
    }

}

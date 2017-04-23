#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    ++argv;
    for(int i = 1; i < argc; i ++, argv ++)
        if(!fork()) execlp(*argv, *argv, NULL);

    for(int i = 1; i < argc; i ++)
        wait(NULL);
    
}

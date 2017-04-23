#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    execv("./prog", argv);
    perror("execvp");

}

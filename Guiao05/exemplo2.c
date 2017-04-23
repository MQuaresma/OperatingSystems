#include <unistd.h>


int main(){

    int pd[2];
    char buf[10];

    pipe(pd);

    write(pd[1], "ab", 2);
    write(pd[1], "cde", 3);

    read(pd[0], buf, 3);
    read(pd[0], buf, 2);

}

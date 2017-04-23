#include "mycat.h"

int main(){

    int c;

    while(read(0, &c, 1) > 0 && c != EOF){
        write(1, &c, 1);         
    }

    return 0;
}

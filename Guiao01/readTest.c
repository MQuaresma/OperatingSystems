#include "guiao01.h"


main(){
    
    char *buf = (char*)malloc(sizeof(char)*20);
    ssize_t res;
    
    res = read(0, buf, 20);
    printf("Read :%lu \n To be read: %d", res, 20); 
    return 0;
}

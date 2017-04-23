#include <sys/types.h>
#include <sys/stat.h>

//int mkfifo(const char *pathname, mode_t mode);

main(){

    int fd = mkfifo("fifo", 666);

}

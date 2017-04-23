#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define LINE 1000


main(){

    int in = open("/etc/passwd", 640), out = open("saida.txt", O_CREAT | O_WRONLY), err = open("erros.txt",  O_CREAT | O_WRONLY);
    char line[LINE];
    ssize_t rd;

    dup2(in, 0);
    close(in);
    dup2(out, 1);
    close(out);
    dup2(err, 2);
    close(err);

    fgets(line, LINE, stdin);
    printf("%s", line);
    fprintf(stderr, "%s", line);

}

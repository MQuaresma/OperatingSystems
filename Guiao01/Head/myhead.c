#include "myhead.h"

// TODO: reduce the no of calls to read


/* 
 * myhead: implementaçao do programa head
 * que devolve, por indicaçao, as n(10 predefiniçao) 
 * primeiras linhas de um documento ou do stdin
 */
 
int main(int argc, char *argv[]){
    
    int nL = LINES, fildes = 0, curLine = 0;
    char *buf = (char*)malloc(sizeof(char)*BLOCK), c;
    ssize_t red;
     
    if(argc > 1){
        ++argv; 
        if(**argv == '-'){
            nL = 0;
            while(*++*argv && isdigit(**argv))
                nL = nL*10+(**argv-'0');
            argc--;
            argv++;
        }
    }

    while(--argc > 0){
        fildes = open(*argv, O_RDONLY);
        if(fildes < 0) fprintf(stderr, "==>File \"%s\" not found<==\n", *argv); 
        else{
            write(1, "==> ", 4); 
            write(1, *argv, strlen(*argv)); 
            write(1, " <==\n", 5); 
            for(curLine = 0; curLine < nL; curLine++)
                while(read(fildes, &c, 1)>0){
                    write(1, &c, 1); 
                    if(c == '\n')
                        break;
                }        
            close(fildes);
        }
        argv ++;
    }
    if(!fildes){
        while(curLine++ < nL)
            while(read(fildes, &c, 1)>0 && c != '\n')
                    write(1, &c, 1); 
    }

}

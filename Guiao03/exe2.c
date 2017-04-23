#include <stdio.h> 
#include <unistd.h>


int main(){

    if(!fork()){
        execlp("ls", "ls", "-l", NULL);     //esta chamada ao sistema substitui o codigo deste processo pelo codigo do comando a executar
        perror("execlp");
    }    

}

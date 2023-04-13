#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int valor = 0;

int main(){
    pid_t pidB;
    int status;

    pidB = fork();
    if(pidB == 0){
        valor = 5;
        printf("Valor em B: %d\n", valor);
    } else {
        wait(&status);
        valor += 10;
        printf("Valor em A: %d\n", valor);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pidA, pidB, pidC;
    int status;

    pidA = getpid();

    pidB = fork();
    if (pidB == -1) {
        perror("Erro ao criar processo B");
        exit(1);
    } else if (pidB == 0) {
        pidC = fork();
        if (pidC == -1){
            perror("Erro ao criar processo B");
            exit(1);
        }else if (pidC == 0) {
            sleep(1);
            printf("Eu sou o processo C, filho de %d\n", getpid());
            exit(0);
        } else {
            wait(&status);
            sleep(1);
            printf("Eu sou o processo B, filho de %d\n", getpid());
            exit(0);
        }
    } else {
        wait(&status);
        sleep(1);
        printf("Eu sou o processo A, PID = %d\n", pidA);
        exit(0);
    }
}
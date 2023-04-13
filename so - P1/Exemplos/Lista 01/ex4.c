/*
 Excrever um programa C que cria uma árvore de 3 processos, 
 onde o processo A faz um fork() criando um processo B, 
 o processo B, por sua vez, faz um fork() criando um processo C.
  Cada processo deve exibir uma mensagem "Eu sou o processo XXX, 
  filho de YYY", onde XXX e YYY são PIDs de processos. Utilizar wait() 
  para garantir que o processo C imprima sua resposta antes do B, e que 
  o processo B imprima sua resposta antes do A. Utilizar sleep() (man 3 sleep) 
  para haver um intervalo de 1 segundo entre cada mensagem impressa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pidA, pidB, pidC;

    pidA = getpid();
    printf("Eu sou o processo A com PID %d\n", pidA);

    pidB = fork();
    if (pidB < 0) {
        perror("fork");
        exit(1);
    } else if (pidB == 0) {
        pidC = fork();
        if (pidC < 0) {
            perror("fork");
            exit(1);
        } else if (pidC == 0) {
            sleep(1);
            printf("Eu sou o processo C com PID %d, filho de %d\n", getpid(), getppid());
        } else {
            wait(NULL);
            sleep(1);
            printf("Eu sou o processo B com PID %d, filho de %d\n", getpid(), getppid());
        }
    } else {
        wait(NULL);
        sleep(1);
        printf("Eu sou o processo A com PID %d\n", pidA);
    }

    return 0;
}
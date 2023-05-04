// Faça um programa utilizando o posix do linux que faça dois processos filhos enviarem mensagem para um mesmo pai por meio de PIPES.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
char *message = "Comp é legal!!!";

int main()
{
    char buf[1024];
    int fd[2];
    int fd2[2];
    //criar um pipe
    pipe(fd); 
    pipe(fd2); 
    int pid = fork();
    int pid2 = fork();

    //criar filho
    if (pid == 0)
    { 
        char *message = "eu sou o processo filho com pid xx";
        //1: mensageiro junto com mensagem a ser lida
        write(fd[1], message, strlen(message) + 1);
    }
    if (pid2 == 0)
    {
        char *message = "eu sou o processo filho com pid x";
        //1: mensageiro junto com mensagem a ser lida
        write(fd2[1], message, strlen(message) + 1);
    }
    

    if (pid!= 0 && pid2 != 0)
    {
        //0: apenas escritas e o tamanho
        read(fd[0], buf, 1024);
        printf("O filho 1 disse: %s\n", buf);

        read(fd2[0], buf, 1024);
        printf("O filho 2 disse: %s\n", buf);
    }
    
   
}
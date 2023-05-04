// Shared Memory, Complete o código a seguir para que os processos pai e filho possam compartilhar um segmento de memória.
// O filho escreve no segmento e o pai imprime na tela o conteúdo da mensagem.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *segmento;
    int modo, filho;
    // criacao do filho
    filho = fork();

    /* Criar a chave: */
    key = ftok("/sys", 'x');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    /*Criar o segmento */
    shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    // Código do filho
    if (filho == 0)
    {
        /*Vincula o segmento de memória á variável segmento*/
        segmento = (char *)shmat(shmid, 0, 0);
        if (segmento == (char *)(-1))
        {
            perror("shmat");
            exit(1);
        }

        printf("ESCREVENDO NO SEGUIMENTO...");
        strncpy(segmento, "olA", SHM_SIZE);

        /* Desvincular do segmento */
        if (shmdt(segmento) == -1)
        {
            perror("shmdt");
            exit(1);
        }
    }
    // Código do pai
    else
    {
        /*Vincula o segmento de memória á variável segmento*/
        segmento = (char *)shmat(shmid, 0, 0);
        if (segmento == (char *)(-1))
        {
            perror("shmat");
            exit(1);
        }

        printf("\nCONTEUDO DO SEGUIMENTO %s\n", segmento);

        /* Desvincular do segmento */
        if (shmdt(segmento) == -1)
        {
            perror("shmdt");
            exit(1);
        }

        // DESTRUIR REGIÃO DE MEMORIA COMPARTILHADA
        shmctl(shmid, IPC_RMID, NULL);
        printf("\nDELETANDO SEGUIMENTO\n");
    }

    return 0;
}

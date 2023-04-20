#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(int argc, char const *argv[])
{
    key_t key;
    int id;
    char *Data;

    // APENAS CRIAR UMA CHAVE A PARTIR DESSE PARAMETRO PEGA STRING E CARACTERE EMBARALHA E CRIA UMA CHAVE
    key = ftok("/sys", 'x');

    // PROXIMO PASSO CRIAÇÃO DE MEMORIA COMPARTILHADA

    // cria região de memoria compartilhada e retorna um id
    id = shmget(key, SHM_SIZE, 0644 | IPC_CREAT);

    // VINCULAR REGIÃO DE MEMORIA COMPARTILHADA A INTERFACE

    Data = (char *)shmat(id, 0, 0);

    if (argc > 1 && !strcmp(argv[1], "apagar"))
    {
        /* SE DIGITARMOS APAGAR ELE APAGA A REGIÃO DE MEMORIA */

        // DESVINCULAR DO PONTEIRO
        shmdt(Data);

        // DESTRUIR REGIÃO DE MEMORIA COMPARTILHADA
        shmctl(id, IPC_RMID, NULL);
        printf("DELETANDO SEGUIMENTO");

        exit(0);
    }

    if (argc == 2)
    {
        /* code */
        printf("ESCREVENDO NO SEGUIMENTO");
        strncpy(Data, argv[1], SHM_SIZE);
    }
    else
    {
        printf("CONTEUDO DO SEGUIMENTO %s\n", Data);
    }

    /*
    a2150336@pxe-ubuntu:~/output$ ./"memoriacompartilhada"
    CONTEUDO DO SEGUIMENTO
    a2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada roda
    ESCREVENDO NO SEGUIMENTOa2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada
    CONTEUDO DO SEGUIMENTO roda
    a2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada apagar
    DELETANDO SEGUIMENTOa2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada
    CONTEUDO DO SEGUIMENTO
    a2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada
    CONTEUDO DO SEGUIMENTO
    a2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada oi
    ESCREVENDO NO SEGUIMENTOa2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada
    CONTEUDO DO SEGUIMENTO oi
    a2150336@pxe-ubuntu:~/output$ ./memoriacompartilhada apagar
    DELETANDO SEGUIMENTO
    */
    return 0;
}

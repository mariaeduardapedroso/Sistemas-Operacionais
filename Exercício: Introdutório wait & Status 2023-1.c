// USAMOS O EXEC QUANDO CRIAMOS UM PROCESSO E QUEREMOS  USAR ALGO
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Excrever um programa C que cria uma árvore de 3 processos, onde o processo A faz um fork() criando um processo B,
o processo B, por sua vez, faz um fork() criando um processo C.
Cada processo deve exibir uma mensagem "Eu sou o processo XXX, filho de YYY", onde XXX e YYY são PIDs de processos.
Utilizar wait() para garantir que o processo C imprima sua resposta antes do B, e que o processo B imprima sua resposta antes do A.
Utilizar sleep() (man 3 sleep) para haver um intervalo de 1 segundo entre cada mensagem impressa.
*/
/*
O status passado como parâmetro à função wait(&status) é, na verdade, o mecanismo de retorno de resultado do wait/waitpid.
Ao retornar, esta variável contém informações sobre o resultado da execução do processo filho. Por exemplo,
se um processo terminou normalmente (i.e., chamou exit), o comando WIFEXITED(status) retorna true.
Este comando retorna false se o processo foi abortado (e.g., segmentation fault) ou morto (e.g., kill).
Investigue no manual do wait no Linux (man wait) o funcionamento do comando WEXITSTATUS(status),
 e use-o para modificar o exercício anterior para calcular o 5!, sendo que cada processo pode executar apenas uma multiplicação.
*/

int main(int argc, char const *argv[])
{

    int pid;
    int status;

    pid = fork(); // FORK É O MOMENTO DA CRIAÇÃO DE UM PROCESSO -> COPIA IDENTICA (FILHO) DO PROGRAMA

    if (pid < 0)
    {
        /* erro no nascimento do filho */
        printf("Erro na chamada fork");
    }

    if (pid == 0)
    {
        /* é o filho que acabou de nascer */

        int pidneto;
        int statusneto;

        pidneto = fork();

        if (pidneto < 0)
        {
            /* erro no nascimento do neto */
            printf("Erro na chamada fork");
        }

        if (pidneto == 0)
        {
            /* é o neto que acabou de nascer */
            sleep(1);
            printf("\nEu sou o processo C %d filho de %d", getpid(), getppid());


        }
        else
        {
            wait(&statusneto);

            if (WIFEXITED(statusneto))
            {
                /* Ve se o exited do neto foi ok e o filho rodou normalmente*/
                // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                printf("\nPrograma do neto rodou normalmente com o codigo: %d", WEXITSTATUS(statusneto));
            }

            if (WIFSIGNALED(statusneto))
            {
                /* Ve se o neto foi interrompido */
                // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                printf("\nPrograma do neto foi morto por um kill com o codigo: %d", WTERMSIG(statusneto));
            }

            sleep(1);
            printf("\nEu sou o processo B %d filho de %d", getpid(), getppid());
        }
    }
    else
    {
        /* é o pai que possui um pid já */
        // FAZ COM QUE O PAI ESPERE O FILHO RODAR PRIMEIRO -> &STATUS É PARA INFORMAR COMO O FILHO TERMINOU (RETURN)
        wait(&status);

        if (WIFEXITED(status))
        {
            /* Ve se o exited do filho foi ok e o filho rodou normalmente*/
            // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
            printf("\nPrograma do filho rodou normalmente com o codigo: %d", WEXITSTATUS(status));
        }

        if (WIFSIGNALED(status))
        {
            /* Ve se o filho foi interrompido */
            // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
            printf("\nPrograma do filho foi morto por um kill com o codigo: %d", WTERMSIG(status));
        }
        
        sleep(1);
        printf("\nEu sou o processo A %d filho de %d", getpid(), getppid());
    }

    return 0;
}

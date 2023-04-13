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

    int pid1;
    int status1;

    pid1 = fork(); // FORK É O MOMENTO DA CRIAÇÃO DE UM PROCESSO -> COPIA IDENTICA (FILHO) DO PROGRAMA

    if (pid1 < 0)
    {
        /* erro no nascimento do filho */
        printf("Erro na chamada fork");
    }

    if (pid1 == 0)
    {
        /* é o filho que acabou de nascer */

        int pid2;
        int status2;

        pid2 = fork();

        if (pid2 < 0)
        {
            /* erro no nascimento do neto */
            printf("Erro na chamada fork");
        }

        if (pid2 == 0)
        {
            /* é o neto que acabou de nascer */
            int pid3;
            int status3;

            pid3 = fork();

            if (pid3 < 0)
            {
                /* erro no nascimento do neto */
                printf("Erro na chamada fork");
            }

            if (pid3 == 0)
            {
                /* é o neto que acabou de nascer */
                int pid4;
                int status4;

                pid4 = fork();

                if (pid4 < 0)
                {
                    /* erro no nascimento do neto */
                    printf("Erro na chamada fork");
                }

                if (pid4 == 0)
                {
                    /* é o neto que acabou de nascer */

                    sleep(1);
                    printf("\nEu sou o processo 4 %d filho de %d", getpid(), getppid());
                    exit(5);
                }
                else
                {
                    wait(&status4);

                    if (WIFEXITED(status4))
                    {
                        /* Ve se o exited do neto foi ok e o filho rodou normalmente*/
                        // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                        printf("\nPrograma do neto rodou normalmente com o codigo: %d", WEXITSTATUS(status4));
                    }

                    if (WIFSIGNALED(status4))
                    {
                        /* Ve se o neto foi interrompido */
                        // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                        printf("\nPrograma do neto foi morto por um kill com o codigo: %d", WTERMSIG(status4));
                    }

                    sleep(1);
                    printf("\nEu sou o processo 3 %d filho de %d", getpid(), getppid());
                    exit(4 * WEXITSTATUS(status4));
                }

                printf("\nEu sou o processo 3 %d filho de %d", getpid(), getppid());
            }
            else
            {
                wait(&status3);

                if (WIFEXITED(status3))
                {
                    /* Ve se o exited do neto foi ok e o filho rodou normalmente*/
                    // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                    printf("\nPrograma do neto rodou normalmente com o codigo: %d", WEXITSTATUS(status3));
                }

                if (WIFSIGNALED(status3))
                {
                    /* Ve se o neto foi interrompido */
                    // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                    printf("\nPrograma do neto foi morto por um kill com o codigo: %d", WTERMSIG(status3));
                }

                sleep(1);
                printf("\nEu sou o processo 2 %d filho de %d", getpid(), getppid());
                exit(3 * WEXITSTATUS(status3));
            }
        }
        else
        {
            wait(&status2);

            if (WIFEXITED(status2))
            {
                /* Ve se o exited do neto foi ok e o filho rodou normalmente*/
                // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                printf("\nPrograma do neto rodou normalmente com o codigo: %d", WEXITSTATUS(status2));
            }

            if (WIFSIGNALED(status2))
            {
                /* Ve se o neto foi interrompido */
                // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
                printf("\nPrograma do neto foi morto por um kill com o codigo: %d", WTERMSIG(status2));
            }

            sleep(1);
            printf("\nEu sou o processo 1 %d filho de %d", getpid(), getppid());
            exit(2 * WEXITSTATUS(status2));
        }
    }
    else
    {
        /* é o pai que possui um pid já */
        // FAZ COM QUE O PAI ESPERE O FILHO RODAR PRIMEIRO -> &STATUS É PARA INFORMAR COMO O FILHO TERMINOU (RETURN)
        wait(&status1);

        if (WIFEXITED(status1))
        {
            /* Ve se o exited do filho foi ok e o filho rodou normalmente*/
            // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
            printf("\nPrograma do filho rodou normalmente com o codigo: %d", WEXITSTATUS(status1));
        }

        if (WIFSIGNALED(status1))
        {
            /* Ve se o filho foi interrompido */
            // TRADUZ O STATUS E MOSTRA O QUE ACONTECEU PEGA O CODIGO DO EXIT
            printf("\nPrograma do filho foi morto por um kill com o codigo: %d", WTERMSIG(status1));
        }

        sleep(1);
        printf("\n5 fatorial == %d\n", WEXITSTATUS(status1));
    }

    return 0;
}

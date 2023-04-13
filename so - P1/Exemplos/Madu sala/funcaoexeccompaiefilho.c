// USAMOS O EXEC QUANDO CRIAMOS UM PROCESSO E QUEREMOS  USAR ALGO
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // IDENTIFICADOR DO PROCESSO (RG DO PROCESSO)
    int pid;
    // ARMAZENA O VALOR DE RETORNO, COMO O FILHO FINALIZOU
    int status;

    // APOS O FORK O PID É ZERO COMO SE FOSSE NOS MESMOS, QUANDO NASCEMOS NÃO TEMOS CPF
    pid = fork(); // FORRK É O MOMENTO DA CRIAÇÃO DE UM PROCESSO -> COPIA IDENTICA (FILHO) DO PROGRAMA
    // RETORNOS:
    //     0  -> filho criado
    //     >0 -> erro na criação do filho

    if (pid < 0)
    {
        /* erro no nascimento do filho */
        printf("Erro na chamada fork");
    }

    if (pid == 0)
    {
        /* é o filho que acabou de nascer */

        // ESSE É O PROGRAMA QUE O FILHO VAI RODAR SE TEM ALGO NO FILHO ESSE CODIGO É TOTALMENTE SUBSTITUIDO PELO NOVO CÓDIGO
        execl("/bin/ls", "ln", "-l", NULL);

        /* RESPOSTA DO TERMINAL
        total 144
        -rwxr-xr-x 1 a2150336 usuarios 75200 mar 30 08:10 execcompaiefilho
        -rwxr-xr-x 1 a2150336 usuarios 67224 mar 30 07:58 main

        Programa do filho rodou normalmente com o codigo: 0
        Pai rodou com pid 7372 e status do filho foi: 0
        */

       //
        printf("Filho pid %d:", getpid());
        while (1)
        {
            /* teste WIFSIGNALED */
            // usar kill junto com pid que quero matar em outro prompt
        }

        // exit(5); //teste WIFEXITED
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

        printf("\nPai rodou com pid %d e status do filho foi: %d", getpid(), status);
    }

    return 0;
}

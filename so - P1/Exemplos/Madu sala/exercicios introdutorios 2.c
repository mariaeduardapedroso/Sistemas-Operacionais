// Pesquise na documentação do POSIX (ou api equivalente no windows), e crie uma função para sua biblioteca para disparar uma mensagem a cada x segundos
// de acordo com a assinatura a seguir:

//  printsinc(char* msg, int segundos);

// Se o usuário apertar a tecla CTRL Z três vezes o programa deverá ser encerrado.

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int i = 0;
char mensagem[100];

int tamanhoString(char *str)
{
    int j = 0;

    while (*str != '\0')
    {
        j++;
        str++;
    }

    return j;
}

void func()
{
    int tamanho = tamanhoString(mensagem);
    write(1, mensagem, tamanho);
}

void func2()
{
    int tamanho = tamanhoString("CONTRLZ.../n");
    write(1, "CONTRLZ...\n", tamanho);
    i++;

    if (i == 3)
    {
        exit(0);
    }
}

void printsinc(char *msg, int segundos)
{
    strcpy(mensagem, msg);
    // SIGNALRM -> DISPARA UM ALARME
    // SIGTSTP -> CONTROLZ

    signal(SIGALRM, func);
    // signal(SIGALRM, func); ESCUTA O SINAL DO EVENTO E GARANTE E TRATA ANTES DE ACONTECER
    signal(SIGTSTP, func2);

    while (1)
    {
        alarm(segundos);
        // ALARME EM SEGUNDOS QUE QUERO DISPARAR
        pause();
        // pause(); GARANTE QUE O SINAL VAI SER PROPAGADO
    }
}

int main()
{
    int size = 100;
    char *nome = (char *)(malloc(size * sizeof(char)));

    nome = "oi\n";

    printsinc(nome, 2);

    return 0;
}

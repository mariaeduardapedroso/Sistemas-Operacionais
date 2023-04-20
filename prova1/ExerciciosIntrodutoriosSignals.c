#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int tamanhoString(char *str)
{
    int i = 0;
    // while (str[i] != '\0')
    // {
    //     i++;
    // }

    while (*str != '\0')
    {
        i++;
        str++;
    }

    return i;
}

void meuPrint(char *str)
{
    int tamanho = tamanhoString(str);
    write(1, str, tamanho);
}

void func()
{
    meuPrint("dentro de um loop\n");
}

void func1()
{
    meuPrint("saindo...\n");
    exit (0);
}



int main()
{
    // SIGNALRM -> DISPARA UM ALARME
    // SIGINT -> SINAL DE INTERRUPÇÃO CONTRLC

    signal(SIGALRM, func);
    // signal(SIGALRM, func); ESCUTA O SINAL DO EVENTO E GARANTE E TRATA ANTES DE ACONTECER
    signal(SIGINT, func1);

    while (1)
    {

        alarm(5);
        // ALARME EM SEGUNDOS QUE QUERO DISPARAR
        pause();
        // pause(); GARANTE QUE O SINAL VAI SER PROPAGADO
    }

    return 0;
}

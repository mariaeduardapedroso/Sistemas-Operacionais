//FAÇA UM PROGRAMA PARA DISPARAR UMA MENSAGEM DE BONS ESTUDOS A CADA 10 SEGUNDOS UTILIZANDO API POSIX DO LINUX
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
    meuPrint("Bons estudos!\n");
}



int main()
{
    // SIGNALRM -> DISPARA UM ALARME


    signal(SIGALRM, func);
    // signal(SIGALRM, func); ESCUTA O SINAL DO EVENTO E GARANTE E TRATA ANTES DE ACONTECER

    while (1)
    {

        alarm(10);
        // ALARME EM SEGUNDOS QUE QUERO DISPARAR
        pause();
        // pause(); GARANTE QUE O SINAL VAI SER PROPAGADO
    }

    return 0;
}

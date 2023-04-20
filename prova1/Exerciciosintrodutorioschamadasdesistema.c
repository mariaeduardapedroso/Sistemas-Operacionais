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

void meuPrintLongInt(long int *num)
{
    int tamanho = sizeof(long int);
    write(1, num, tamanho);
}

int main()
{
    int size = 100;
    char *nome = (char *)(malloc(size * sizeof(char)));
    long int ra;

    meuPrint("Digite seu nome:");
    read(0, nome, size);

    meuPrint("Digite seu ra:");
    read(0, &ra, sizeof(long int));

    meuPrint("Dados:\n");
    meuPrint(nome);
    meuPrintLongInt(&ra);
    return 0;
}

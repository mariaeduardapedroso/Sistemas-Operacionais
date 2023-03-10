#include <unistd.h>
#include <stdlib.h>
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

int main()
{
    /*
        char *msg = (char *)(malloc(20 * sizeof(char)));
        msg = "0i";
        write(1, "oi mensagem",11);
        write(1, msg, 2);
    */
    meuPrint("vai toma no cooler\n");

    return 0;
}

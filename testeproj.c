#define _XOPEN_SOURCE_EXTENDED 1
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

void imprima(char *string, ...)
{
    // tipo de objeto completo adequado para armazenar as informações necessárias para as macros
    va_list argumentoRecebido;

    // permite o acesso a argumentos de funções variáveis
    va_start(argumentoRecebido, string);

    int size;
    int i = 0;

    while (string[i] != '\0')
    {

        if (string[i] == '%')
        {

            i++;
            switch (string[i])
            {
            case 's':
                char *palavra = va_arg(argumentoRecebido, char *);
                size = strlen(palavra);
                write(1, palavra, size);
                break;

            case 'c':
                char *caracter = va_arg(argumentoRecebido, char *);
                write(1, &caracter, 1);
                break;

            case 'd':
            case 'i':
                long inteiro = va_arg(argumentoRecebido, int);
                int tamanho = snprintf(NULL, 0, "%ld", inteiro);
                char *buffer = malloc(tamanho + 1);
                snprintf(buffer, tamanho + 1, "%ld", inteiro);
                write(1, buffer, sizeof(inteiro));
                break;

            case 'f':
                double flutuante = va_arg(argumentoRecebido, double);
                char buffer[100];
                gcvt(flutuante, 10, buffer);
                write(1, buffer, sizeof(flutuante));
                break;

            case '.':
                if (string[i+2] == 0)
                {
                    /* code */
                }
                else
                {
                    double flutuante = va_arg(argumentoRecebido, double);
                    int numero = (int)(string[i + 1] - '0');
                    char buffer[100];
                    gcvt(flutuante, contar_digitos((int)flutuante) + numero, buffer);
                    write(1, buffer, sizeof((int)flutuante) + numero);
                    i += 2;
                }
                break;

            default:
                write(1, "ERRO NO PRINTF\n", 16);
                break;
            }
            if (string[i] == 's')
            {

                // char *palavra = va_arg(argumentoRecebido, char *);
                // size = strlen(palavra);
                // write(1, palavra, size);
            }
            else if (string[i] == 'd' || string[i] == 'i')
            {

                // long inteiro = va_arg(argumentoRecebido, int);
                // int tamanho = snprintf(NULL, 0, "%ld", inteiro);
                // char *buffer = malloc(tamanho + 1);
                // snprintf(buffer, tamanho + 1, "%ld", inteiro);
                // write(1, buffer, sizeof(inteiro));
            }
            else if (string[i] == 'c')
            {
                // char *caracter = va_arg(argumentoRecebido, char *);
                // write(1, &caracter, 1);
            }
            else if (string[i] == 'f')
            {

                // double flutuante = va_arg(argumentoRecebido, double);
                // char buffer[100];
                // gcvt(flutuante, 10, buffer);
                // write(1, buffer, sizeof(flutuante));
            }
            else if (string[i] == '0' && string[i + 1] == '.' && (string[i + 2] == '1' || string[i + 2] == '2' || string[i + 2] == '3') && string[i + 3] == 'f')
            {

                double flutuante = va_arg(argumentoRecebido, double);
                int numero = (int)(string[i + 2] - '0');
                char buffer[100];
                gcvt(flutuante, contar_digitos((int)flutuante) + numero, buffer);
                write(1, buffer, sizeof((int)flutuante) + numero);
                i += 3;
            }
            else if (string[i] == '.' && (string[i + 1] == '1' || string[i + 1] == '2' || string[i + 1] == '3') && string[i + 2] == 'f')
            {

                // double flutuante = va_arg(argumentoRecebido, double);
                // int numero = (int)(string[i + 1] - '0');
                // char buffer[100];
                // gcvt(flutuante, contar_digitos((int)flutuante) + numero, buffer);
                // write(1, buffer, sizeof((int)flutuante) + numero);
                // i += 2;
            }
        }
        else
        {

            write(1, &string[i], 1);
        }
        i++;
    }

    va_end(argumentoRecebido);
}

int contar_digitos(int n)
{
    int count = 0;
    do
    {
        n /= 10;
        ++count;
    } while (n != 0);
    return count;
}

void main()
{

    char *str = "Alo Alo";

    int inteiro1 = 34657;
    int inteiro2 = 31225;
    int inteiro3 = 3222;
    char caracter = 'e';
    double flutuante = 323.2333;
    float flutuante1 = 12.453;
    float flutuante2 = 12.332;

    imprima(" Olá mundo!!!!!\n");

    imprima(" %s\n", str);

    imprima(" Numeros sortidos %i \n", inteiro1);

    imprima(" Numeros sortidos %c \n", caracter);

    imprima(" Numeros sortidos %f \n", flutuante);

    imprima(" Numeros sortidos %d %f %d %f %d e um caracter %c\n", inteiro1, flutuante1, inteiro2, flutuante2, inteiro3, caracter);

    imprima(" Numeros sortidos %0.3f\n", flutuante1);

    imprima(" Numeros sortidos %.2f\n", flutuante1);
}

// #define _XOPEN_SOURCE_EXTENDED 1
// #include <string.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <stdarg.h>
// #include <stdio.h>
// #include <math.h>
// int tamanhoString(char *str, ...)
// {
//     int i = 0;

//     while (*str != '\0')
//     {
//         i++;
//         str++;
//     }

//     return i;
// }

// void meuPrint(char *str)
// {
//     int tamanho = tamanhoString(str);
//     write(1, str, tamanho);
// }

// void imprimir(char *string, ...)
// {
//     char str[100];
//     va_list argumentos;
//   	va_start(argumentos, string);

//     // while (string != '\0')
//     // {
//     //     if (string == '%')
//     //     {
//     //         sprintf(str, string, format);
//     //         format++;r
//     //     }
//     //     string++;
//     // }

//     // A função sprintf serve para formatar uma string e guardar o resultado em um array (na realidade, ela aceita um ponteiro).
//     sprintf(str, string, format);
//     meuPrint(str);

//     return (0);
// }

// int main()
// {
//     float sla = 1.2345;
//     imprimir("oi %.2f tudo bem", sla);

//     return 0;
// }

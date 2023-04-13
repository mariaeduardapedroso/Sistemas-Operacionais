#include <string.h>
#include <stdlib.h>

// Utilize os caracteres de escape "\033[ B\033[ C" para montar as mensagens a serem escritas:

void myprintf(int x, int y, char *msg)
{

    int size = strlen(msg);
    char msg2[11];
    strcpy(msg2, "\033[ B\033[ C");

    msg2[2] = x + '0';
    msg2[6] = y + '0';

        write (1,msg2, 11);
        write(1, msg, 2);
}

int main()
{

    char *msg = (char *)(malloc(20 * sizeof(char)));
    msg = "0i";

    myprintf(8, 5, msg);
    return 0;
}

//gcc -o nome do exec nome do arquivo
//./nome do exec

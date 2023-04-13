/*
Crie um processo para printar na tela uma lista de processos em execução no sistema.
DICA: usar o programa ps
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if(pid == 0) {
        execlp("ps", "ps", "-ef", NULL);
        perror("execlp");
        exit(1);
    } else if(pid < 0) {
        perror("fork");
        exit(1);
    } else {
        wait(NULL);
        printf("Processo filho terminou.\n");
    }

    return 0;
}
/*
Este programa cria um processo filho usando a função fork(). O processo filho chama a 
função execlp() para executar o comando ps -ef, que imprime uma lista de processos em 
execução no sistema. O processo pai aguarda a conclusão do processo filho usando a 
função wait(), e depois imprime uma mensagem na tela.

Para compilar o programa acima em um sistema Linux, você pode executar o seguinte 
comando em um terminal:
gcc -o pslist pslist.c
Isso criará um arquivo executável chamado "pslist". Você pode executá-lo com o 
seguinte comando:
 ./pslist
 */
/*
Um procedimento para contar o número de vezes que o usuário enviou o sinal SIGINT 
para o processo em execução. Pressionar Ctl-C no teclado envia esse sinal. 
Quando o processo recebe o sinal SIGTSTP (Ctl-Z), 
ele deve imprimir no terminal o número de sinais SIGINT que recebeu. 
Depois de receber 3 sinais SIGINT, o programa deve perguntar se o usuário 
deseja sair do programa. Se o usuário não responder em 20 segundos, 
um sinal SIGALRM deve forçar a saída do programa.
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

volatile int count = 0;
volatile int should_exit = 0;

void sigint_handler(int sig) {
    count++;
    if(count >= 3) {
        printf("\nRealmente deseja sair? [Y/n]: ");
        fflush(stdout);
        char answer[256];
        signal(SIGALRM, exit_handler);
        alarm(20);
        fgets(answer, 256, stdin);
        alarm(0);
        if(answer[0] == 'Y' || answer[0] == 'y') {
            should_exit = 1;
        }
        count = 0;
    }
}

void sigtstp_handler(int sig) {
    printf("\nVocê apertou Ctl-C '%d' vezes\n\n", count);
    count = 0;
}

void exit_handler(int sig) {
    printf("\nDemorou muito para responder. Saindo......\n");
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    printf("Pressione Ctl-C para contar.\n");
    printf("Pressione Ctl-Z para mostrar o número de contagens.\n\n");

    while(!should_exit) {
        pause();
    }

    printf("\nSaindo...\n");
    return 0;
}
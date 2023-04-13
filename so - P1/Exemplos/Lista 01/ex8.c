/*
A seguinte informação: "processos pai e filho compartilham código, mas não dados"; 
é verdadeira? Demonstre a sua resposta com um programa - exemplo em linguagem c.

A informação é verdadeira. Quando um processo filho é criado através do sistema de 
chamadas fork(), ele recebe uma cópia do espaço de endereçamento do processo pai. 
Essa cópia inclui o código do processo pai, bem como todas as variáveis globais e 
estáticas. No entanto, o processo pai e o processo filho têm seu próprio espaço de 
endereçamento separado para as variáveis locais.

Para demonstrar isso, podemos criar um programa em C que define uma variável global e,
 em seguida, faz um fork() para criar um processo filho. Cada processo incrementa o 
 valor dessa variável e imprime seu valor na tela. Se o processo pai e o processo filho
  compartilhassem o mesmo espaço de endereçamento para essa variável global, veríamos 
  que cada processo afetaria o valor da variável do outro. No entanto, como veremos, 
  isso não acontece.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 0;

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Processo filho
        printf("Processo filho - global_var: %d\n", ++global_var);
    } else {
        // Processo pai
        printf("Processo pai - global_var: %d\n", ++global_var);
    }

    return 0;
}

/*
Processo pai - global_var: 1
Processo filho - global_var: 1
Como podemos ver, cada processo incrementou a variável global_var em 1, 
mas os valores impressos foram 1 para cada processo separadamente. 
Isso confirma que, embora os processos pai e filho compartilhem o mesmo código, 
eles têm seu próprio espaço de endereçamento para as variáveis locais, incluindo 
as variáveis globais e estáticas.
*/
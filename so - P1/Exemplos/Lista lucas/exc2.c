//Exercício 2
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int contador = 0;
char buf[2];

void func3() {
    write(1, "Forçando saída...\n", 18);
	exit(1);
}

void func1(){
    contador++;
    if (contador == 3){
        signal(SIGALRM, func3);
        alarm(5);
        write(1, "Deseja sair do programa? [Y/n]: ", 32);
        read(1, buf, 2);
        if(buf[0] == 'n'){
			write(1, "continuando...\n", 15);
			contador = 0;
			alarm(0);
		}else if(buf[0] =='y'){
			write(1, "Saindo do programa\n", 19);
			exit(1);
		}
    }
}

void func2(){
    char buffer[100]; 
	char* string = "Voce apertou ctrl-c %d vezes\n";
	int tamanho = sprintf(buffer, string, contador);
	write(1, buffer, tamanho);
}

int main() {
    signal(SIGINT, func1);
    signal(SIGTSTP, func2);
    signal(SIGALRM, func3);
    while(1);
    return 0;
}


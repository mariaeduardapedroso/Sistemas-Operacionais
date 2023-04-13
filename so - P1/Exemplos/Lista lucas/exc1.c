//Exercício 1

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void func(){
    char msg[20]= "Bons estudos!\n";
    write(1, msg, strlen(msg));
}

int main() {
    signal(SIGALRM, func);
    while(1){
        alarm(10);
        pause();
    }
    return 0;
}
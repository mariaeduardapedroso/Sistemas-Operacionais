#define _XOPEN_SOURCE_EXTENDED 1
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>






void imprima(char* frasePassada, ...){
	// um tipo de objeto completo adequado para armazenar as informações necessárias para as macros
	va_list args;

	//Permite o acesso a argumentos de funções variáveis
  	va_start(args, frasePassada);
	
	char buffer[100];
  	int size;
  	int i=0;
  	while (frasePassada[i] != '\0'){

		if (frasePassada[i] == '%'){

	    		i++;
				switch (frasePassada[i])
				{
					case 's':
						//va_arg acessa o próximo argumento de função variádica
						char *palavra = va_arg(args, char*);
		      	    	size = strlen(palavra);
		      			write(1, palavra, size);
					break;

					case 'c':
						//va_arg acessa o próximo argumento de função variádica
						char *caracter = va_arg(args, char*);
						write(1, &caracter, 1);
					break;

					case 'd':case 'i':
						//va_arg acessa o próximo argumento de função variádica
						int inteiro = va_arg(args, int);
						buffer[0]='\0';
						sprintf(buffer,"%d",inteiro);
						write(1, buffer, sizeof(inteiro));
					break;

					case 'f':
						double flutuante = va_arg(args, double);
						buffer[0] = '\0';
						sprintf(buffer,"%f",flutuante);
						write(1, buffer, sizeof(flutuante));
					break;

					case '.'://1 2 3
					if ((frasePassada[i+1]<=51 && frasePassada[i+1]>=49) && frasePassada[i+2] == 'f')
					{
						double flutuante = va_arg(args, double);
						buffer[0] = '\0';
						char tipofloat[] = {'%','.',(char)frasePassada[i+1],'f'};
						//write(1,tipofloat,4);
						sprintf(buffer,tipofloat,flutuante);
						write(1, buffer, sizeof(flutuante));
						i= i + 2;
					}else{
						write(1, "Erro na sintaxe do printf", 25);
					}
					break;

					case '0'://.1 .2 .3 todo 4 5
					if (frasePassada[i+1] == '.' && (frasePassada[i+2]<=51 && frasePassada[i+2]>=49))
					{
						double flutuante = va_arg(args, double);
						buffer[0] = '\0';
						char tipofloat[] = {'%','0','.',(char)frasePassada[i+2],'f'};
						//write(1,tipofloat,5);
						sprintf(buffer,tipofloat,flutuante);
						write(1, buffer, sizeof(flutuante));
						i = i + 3;
						
					}else{
						write(1, "Erro na sintaxe do printf", 25);
					}
					break;

				default:
					write(1, "Erro na sintaxe do printf", 25);
					break;
				}

		}else{

		write(1, &frasePassada[i], 1);
		}
		i++;
  	}

	//termina a travessia dos argumentos da função variádica
  	va_end(args);
}







int main(){

	char *str = "Isso é uma string";
	char caracter = 'M';

	int inteiro1 = 34657;
	int inteiro2 = 31225;
	int inteiro3 = 3222;

	float flutuante1 = 12.453976;
	float flutuante2 = 12.332;
	float flutuante3 = 323.23001;

	//EXERCICIO 1
	imprima("TRABALHO DE SO\n");
	imprima("%s\n\n",str);

	//EXERCICIO 2
	imprima("Inteiro %i \n",  inteiro1);
	imprima("Inteiro %d \n",  inteiro2);
	imprima("Caractere %c \n",  caracter);
	imprima("Float %f \n\n",  flutuante1);

	//EXERCICIO3
	imprima("Numeros %d %f %d %f %d e caracter %c\n\n",  inteiro1, flutuante1, inteiro2, flutuante2, inteiro3, caracter);
	
	//EXERCICIO 4
	imprima("Flutuante com 3 pontos %0.3f\n", flutuante1);
	imprima("Flutuante com 2 pontos %0.2f\n",  flutuante1);
	imprima("Flutuante com 3 pontos %0.3f\n", flutuante1);


	return 0;
}

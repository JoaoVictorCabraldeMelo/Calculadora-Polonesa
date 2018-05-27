#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"


int main () {

	stack *top_stack = alloc_stack();

	stack_float *top = alloc_stack_float();

	int modo;

	char expressao[10000];

	char *expressao_nova;

	printf("\n\n\n\n");

	printf("///////////  Bem - Vindo a Calculadora Pol ///////////\n");
	printf("\n\nEscolha seu modo [1]-Modo Expressao [2]-Modo Calculadora [3]-Quit\n");

	scanf("%d", &modo);

	while(modo != 1 && modo != 2 && modo != 3){
		printf("Esse modo escolhido não e válido\n");
		scanf("%d", &modo);
	}

	while(modo != 3){

		if(modo == 1){

			printf("\n\n\n\n");

			printf("--------------------Bem - Vindo ao Modo Expressao --------------------\n");

			printf("\n\n\n\n");

			printf("Digite uma expressao envolto de escopos ex:(2.00+2.00) ou [9.00*9.00] ou {2.00*3.00(2.00+2.00)}\n");
			printf("ALERTA:Todos os numeros digitados devem ter duas casas(não mais nem menos) depois do ponto ou virgula \n");

			scanf("%s", expressao);

			while(verify_expression(expressao) != 1){

				scanf("%s", expressao);

			}

			expressao_nova = transform_in_sufix(expressao);

			catch_expression_float(top,expressao_nova);

			printf("\n");

			printf("O resultado da expressão e: %.2f\n", top->tp->number);

			printf("\n");
		}

		else if(modo == 2){

			printf("\n\n\n\n");

			printf("--------------------Bem - Vindo ao Calculadora --------------------\n");

			printf("\n\n\n\n");

			printf("As operadores do modo calculadora que funciona como uma pilha sendo +, - , * , / e os especiais como +!,-!,*!,c\n");
			printf("Caso queira sair do modo so aperta 'q'\n");
			printf("ALERTA:Todos os numeros digitados devem ter duas casas(não mais nem menos) depois do ponto ou virgula \n");

			modo_calculadora();
		}

		printf("Deseja continuar ? Se desejar digite [1]-Modo Expressao e [2]-Modo Calculadora caso contrario digite [3]-Quit\n");
		scanf("%d", &modo);
	}

	release_stack_float(top);

	release_stack(top_stack);

	return 0;
}
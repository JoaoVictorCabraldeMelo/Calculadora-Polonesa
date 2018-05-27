/**
*@file calculator.c
*@author João Victor Cabral de Melo
*@date 14 May 2018
*@brief O arquivo implementa as funções que estão no header
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculator.h"

/**
*	@brief a função alloc_stack faz um malloc do tipo stack e coloca NULL no top
*	@return ptr
*
*/

stack *alloc_stack(){

	stack *ptr = malloc(sizeof(stack));/** faz malloc pro ptr do tipo stack */

	ptr->top = NULL;/** bota o top do ptr pra NULL */

	return ptr;/** retorna ptr */
}

/**
*	@brief a função alloc_number cria um elemento para colocar na pilha 
*	@param valua
* 	@return variable 
*/

element *alloc_number(char value){

	element * variable = malloc(sizeof(element));/** faz alloc pro ptr de variable */

	variable->expression = value;/**variable expression recebe value */

	variable->next = NULL;/** seta next como NULL */

	return variable;/** retorna variable */
}

/**
*	@brief a função is_empty retorna falso se top for diferente de NULL se for NULL retorna True 
*	@param top
* 	@return bool 
*/

int is_empty(stack *top){
	return (top->top == NULL);/** retorna bool */
}

/**
*	@brief a função push_stack empilha o char na pilha 
*	@param1 value @param2 top
* 	@return @c void 
*/

void push_stack(char value, stack *top){

	element *variable = alloc_number(value);/** alloca estrutura do tipo elemento na variable */

	variable->next = top->top; /** proximo da variable aponta pro top */

	top->top       = variable; /** top recebe variable */

}

/**
*	@brief a função print_stack printa a pilha  
*	@param top
* 	@return @c void 
*/

void print_stack(stack *top){

	element *aux = top->top;/** cria um ponteiro auxiliar pro top da pilha */

	while(aux != NULL){/**vai ficar subindo na pilha enquanto nao chegar no seu final */
		printf("%c \n", aux->expression);
		aux = aux->next;/** vai pro proximo */
	}
}


/**
*	@brief a função pop desempilha da pilha e retorna o elemento desempilhado se a pilha estiver vazia então ela retorna '0' que e do tipo char  
*	@param top
* 	@return variable
*	@return '0' do tipo char 
*/

char pop(stack *top){

	if(!is_empty(top)){/**pilha não esta vazia */

		element *aux = top->top;/** entao aux aponta para topo */

		top->top = aux->next;/** topo recebe o proximo de aux */

		char variable = aux->expression;/** bota char numa nova variavel */

		free(aux);/** libera o ponteiro pra variavel aux */

		return variable;/** retorna aux */

	}
	else {/** se pilha estiver vazia então retorna NULL */
		printf("A pilha esta vazia não posso desempilhar de pilha vazia\n");
		return '0';
	}
}

/**
*	@brief a função release_stack() desempilha toda a pilha e libera todos os ponteiros alocados  
*	@param top
* 	@return void
*/

void release_stack(stack *top){


	element *aux = top->top;/** aponta pro topo */

	while(aux != NULL){/** enquanto o ponteiro que anda na estrutura for diferente de NULL*/

		top->top = aux->next;/** topo vai pro proximo */

		free(aux);/** libera o ponteiro pro topo */

		aux = top->top;/** ponteiro aponta pro novo topo */

	}

	free(top);/** free no ponteiro do topo*/

}

/**
*	@brief a função catch_expression() recebe uma string e empilha char por char  
*	@param1 top @param2 expression
* 	@return void
*/

void catch_expression(stack *top, char *expression){

	int i;/** contaddor*/

	for(i = 0;i < strlen(expression);i++){/** para i até i o tamanho maximo de expression empilha */
		push_stack(expression[i], top);/** empilha e expression */
	}
}

/**
*	@brief a função verify_expression() recebe uma string e empilha os escopos de abertura se ele achar um escopo que fecha ele vai
*	desempilhar da pilha e vai verificar se e da familia do escopo no final ele verifica se a pilha não esta vazia se ela não estiver
*	os escopo não possui um escopo que fecha então a expressão e invalida    
*	@param1 expression
* 	@return bool como 1= True e 1 != False 
*/

int verify_expression(char *expression){

	stack *new_stack = alloc_stack();/**aloca nova pilha */

	int i;/**contador*/

	for(i =0; i < strlen(expression); i++){/**enquanto não terminar a string faça os testes*/

		switch(expression[i]){/**entra no switch o char */

			case '(':/** se for abrir escopo e empilhado */

				push_stack(expression[i],new_stack);/** empilha char */

				break;

			case '[':/** se for abrir escopo e empilhado */

				push_stack(expression[i],new_stack);/** empilha char */

				break;

			case '{':/** se for abrir escopo e empilhado */

				push_stack(expression[i], new_stack);/** empilha char */

				break;

			case ')':/** se for fechar escopo desempilha e verifica se pilha já não esta vazia */
				
				if(is_empty(new_stack)){/**verifica se a pilha esta vazia*/
					printf("-------------Equação não é valida------------------\n");/**print equação não e valida pois significa que ela não tem
																					*  escopo de abertura*/
					release_stack(new_stack);/** desempilha o que sobrou*/
					return -1;
				}
				else {

					char open_esc = pop(new_stack);/**desempilha */

					if(open_esc != '('){/** verifica se o char desempilhado e o seu par */
					printf("-------------Equação não é valida------------------\n");/**printa equação não e valida */
					release_stack(new_stack);/** desempilha o que sobrou*/
					return -1;
					}
				}

				break;

			case ']':

				if(is_empty(new_stack)){/** verifica se o char desempilhado e o seu par*/
					printf("-------------Equação não é valida------------------\n");/**printa equação não e valida */
					release_stack(new_stack);/** desempilha o que sobrou */
					return -1;
				}
				else {
					char open_esc = pop(new_stack);/**desempilha*/

					if(open_esc != '['){/** verifica se o char desempilhado e o seu par*/
					printf("-------------Equação não é valida------------------\n");/**printa equação não e valida */
					release_stack(new_stack);/** desempilha o que sobrou*/
					return -1;
					}
				}

				break;

			case '}':

				if(is_empty(new_stack)){/** verifica se o char desempilhado e o seu par*/
					printf("-------------Equação não é valida------------------\n");/**printa equação não e valida */
					release_stack(new_stack);/** desempilha o que sobrou*/
					return -1;
				}
				else {
					char open_esc = pop(new_stack);/** desempilha */

					if(open_esc != '{'){/** verifica se o char desempilhado e o seu par*/
					printf("-------------Equação não é valida------------------\n");/**printa equação não e valida */
					release_stack(new_stack);/** desempilha o que sobrou*/
					return -1;
					}					
				}

				break;		
		}
	}

	if(!is_empty(new_stack)){/** depois de parear os escopos se ainda estiver algum escopo na pilha então a expressão não válida */
		printf("-------------Equação não é valida------------------\n");/**printa equação não e valida */
		release_stack(new_stack);/**libera o resto da pilha */
	}
}

/**
*	@brief a função transform_in_sufix() recebe uma string expression ela aloca uma pilha caso ache uma abre parenteses ele empillha caso nao ache
*	um operando então ele vai colocar uma copia na string que vai sair da função caso ache um operando vai desempilha ate achar um escopo que abre     
*	@param1 expression
* 	@return expressão em sufixo
*/

char  *transform_in_sufix(char *expression){

	stack *new_stack = alloc_stack();/** aloca pilha */

	char *sufix;/** string que vai ser retornada*/

	char variable;/** variavel que segura o que retorna no pop()*/

	int i, j = 0;/** contadores */

	for(i = 0; i < strlen(expression); i++){/** anda na string */

		switch(expression[i]){/** casos */

			case '(':/** caso escopo de abertura empilha */
			case '[':
			case '{':
				push_stack(expression[i], new_stack);/** empilha o escopo */
				break;

			case '+':/** caso operando de baixa prioridade */
			case '-':

				variable = pop(new_stack);/** desempilha */

				while(!is_empty(new_stack) && variable != '(' && variable != '[' && variable != '{'){/** enquanto nao estiver vazia ou abrir escopo */
					sufix[j++] = variable;/**faz copia */
					variable = pop(new_stack);/** desempilha */
				}

				push_stack(variable, new_stack);/** empilha variavel */

				push_stack(expression[i], new_stack);/** empilha char */

				break;

			case '*':
			case '/':

				variable = pop(new_stack);/** desempilha */

				while(!is_empty(new_stack) && variable != '(' && variable != '[' && variable != '{' && variable != '+' && variable != '-'){/** enquanto nao estiver vazia ou abrir escopo */
					sufix[j++] = variable;/** faz copia */
					variable = pop(new_stack);/** desempilha */
				}

				push_stack(variable, new_stack);/** empilha variavel*/
				
				push_stack(expression[i], new_stack);/** empilha expressão*/

				break;


			case ')':
				
				variable = pop(new_stack);/** desempilha */

				while(variable != '('){/** nao achar abrir faz copia e empilha  */
					sufix[j++] = variable;/** faz copia */
					variable = pop(new_stack);/** desempilha */
				}
					
				break;

			case ']':
				variable = pop(new_stack);/** desempilha */

				while(variable != '['){/** nao achar abrir faz copia e empilha  */
					sufix[j++] = variable;/** faz copia */
					variable = pop(new_stack);/** desempilha */
				}
					
				break;

			case '}':
				variable = pop(new_stack);/** idem */

				while(variable != '{'){/** enquanto nao achar um abre escopo */
					sufix[j++] = variable;/** faz copia */
					variable = pop(new_stack);/** desempilha */
				}

				break;


			default:
			sufix[j++] = expression[i];/** so faz caso nao for operador ou abertura ou fechamento de escopo*/
		}
	}

	sufix[j] = '\0';/** seta o fim da string */

	return sufix;

}

/**@brief a função aloca uma pilha do tipo float
*@param void
*@return ponteiro pra pilha   
*/

stack_float *alloc_stack_float(){

	stack_float *pointer = malloc(sizeof(stack_float));/**faz malloc() pro ponteiro do tipo stack_float()*/

	pointer->tp = NULL;/** aponta pra nulo */

	return pointer;/** retorna ponteiro */
}

/**@brief a função aloca uma variavel do tipo float e seta na pilha
*@param void
*@return ponteiro pra o elemento_float  
*/

element_float *alloc_number_float(float value){


	element_float *variable = malloc(sizeof(element));/** faz alloc pro ptr de variable */

	variable->number = value;/**variable number recebe value */

	variable->n = NULL;/** seta next como NULL */

	return variable;/** retorna variable */

}

/**@brief a função push_stack_float() coloca numero na pilha
*	@param1 float value  @param2 stack_float ponteiro pro topo 
*@return void  
*/

void push_stack_float(float value, stack_float *top){

	element_float *variable = alloc_number_float(value);/** alloca estrutura do tipo elemento na variable */

		variable->n = top->tp; /** proximo da variable aponta pro top */

		top->tp     = variable; /** top recebe variable */
}

/**@brief a função print_stack_float() printa uma pilha de floats
*@param stack_float ponteiro pro topo
*@return void  
*/


void print_stack_float(stack_float *top){

	element_float *aux = top->tp;/** cria um ponteiro auxiliar pro top da pilha */

	while(aux != NULL){/**vai ficar subindo na pilha enquanto nao chegar no seu final */
		printf("%.2f \n", aux->number);
		aux = aux->n;/** vai pro proximo */
	}
}

/**@brief a função is_empty_float() verifica se a pilha esta vazia 
*@param ponteiro do stack_float pro topo
*@return int do tipo bool  
*/

int is_empty_float(stack_float *top){
	return(top->tp == NULL);/**verifica se a pilha não esta vazia */
}

/**@brief a função pop_float() desempilha pilha do tipo float 
*@param ponteiro do stack_float pro topo
*@return variable desempilhada 
*/

float pop_float(stack_float *top){

	if(!is_empty_float(top)){/**pilha não esta vazia */

		element_float *aux = top->tp;/** entao aux aponta para topo */

		top->tp = aux->n;/** topo recebe o proximo de aux */

		float variable = aux->number;/** bota char numa nova variavel */

		free(aux);/** libera o ponteiro pra variavel aux */

		return variable;/** retorna aux */

	}
	else {/** se pilha estiver vazia então retorna NULL */
		printf("A pilha esta vazia não posso desempilhar de pilha vazia\n");
		return 0;
	}

}

/**@brief a função release_stack_float() libera toda pilha 
*@param ponteiro do stack_float pro topo
*@return void
*/


void release_stack_float(stack_float *top){

	element_float *aux = top->tp;/** aponta pro topo */

	while(aux != NULL){/** enquanto o ponteiro que anda na estrutura for diferente de NULL*/

		top->tp = aux->n;/** topo vai pro proximo */

		free(aux);/** libera o ponteiro pro topo */

		aux = top->tp;/** ponteiro aponta pro novo topo */

	}

	free(top);/** free no ponteiro do topo*/
}


/**@brief a função string_to_float() transforma a string a float  
*@param n 
*@return number 
*/

float string_to_float(char *n){

	float number = 0;/**seta o valor do numero pra 0*/

	float x;/** variavel que recebe transformação */

	int count1 = 0, count2 = 0, i = 0;/**seta contadores*/

	while(n[i] != ',' && n[i] != '.'){/**enquanto nao encontrar , ou . conta os numeros */

		count1++;
		i++;
	}

	i = 0;

	count2 = count1;/**contador 2 recebe o contador 1*/

	for(i = 0; i < count1;i++){/**de 0 ate os numeros antes do . ou , faça */

		x = ((float) n[i]) - 48;/** transforma o char em float */

		number += x * (pow(10,count2 - 1));/**faz a soma usando potencia 10 no number */

		count2--;/**conta2 -- */
	}

	for(i = count1 + 1; n[i] != '\0'; i++){/**agr e dpois do . ou , */

		x = ((float) n[i]) - 48;/** transforma o char em float */

		number += x * (pow(10,count2 - 1));/** soma com potencia dez o numero */

		count2--;/** conta menos */
	}

	return number;/**retorna numero */
}

/**@brief a função catch_expression_float() a pega a expressão sufixa e faz os calculos na pilha deixando 
*	apenas com um resultado no final  
*@param ponteiro pro top de uma pilha de float @param string sufixa
*@return void
*/

void catch_expression_float(stack_float *top, char *expression){

	char number[10000];/**vetor da string */

	int i, j = 0;/**contadores */

	float a, b, sum, divi, dif, mult;/** variaveis usadas nas contas */

	for(i = 0;expression[i] != '\0';i++){/**anda na string */

		switch(expression[i]){/**switch de casos */

			case '.':/**caso for ponto pega os dois numeros depois do ponto ou virgula */
			case ',':

				number[j] = expression[i];/**pega ponto ou virgula */
				number[j + 1] = expression[i + 1];/** pega numero depois da virgual ou ponto */
				number[j + 2] = expression[i + 2];/** pega segundo numero depois da virgula ou ponto */

				float x = string_to_float(number);/** transforma a string pega em float */

				push_stack_float(x,top);/** empilha o float */

				i += 2;/** seta o i pra depois dos valores da virgula */

				j = 0;/** seta o j pra zero pra resetar a string */

				memset(number, 0, sizeof(number));/** reseta a string number pra uma mais nova */


				break;

			case '+':

				a = pop_float(top);/** desempilha primeiro valor */

				b = pop_float(top);/** desempilha segunda valor */

				sum = a + b;/** faz a soma */

				push_stack_float(sum,top);/** empilha valor resultado */

				break;

			case '-':

				a = pop_float(top);/** desempilha primeiro valor */

				b = pop_float(top);/** desempilha segundo valor */

				dif = b - a;/**faz a diferença */

				push_stack_float(dif,top);/**empilha o valor resultado */

				break;

			case '*':

				a = pop_float(top);/** desempilha primeiro valor */

				b = pop_float(top);/** desempilha segundo valor */

				mult = a * b;/** faz a multiplicação */

				push_stack_float(mult,top);/**empilha valor resultado */

				break;

			case '/':

				a    = pop_float(top);/**desempilha primeiro valor */

				b    = pop_float(top);/** desempilha segundo valor */

				divi = b / a;/** faz a divisão */

				push_stack_float(divi,top);/** empilha valor resultado */

				break;


			default:

				number[j++] = expression[i];/** caso for numero vai so fazer copia */

		}

	}

}

/**@brief a função modo_calculadora() começa uma pilha vazia com os operandos normais e operandos especiais como *! +! -! 
*
*
*@return void
*/


void modo_calculadora(){

	stack_float *top = alloc_stack_float();/** inicia pilha vazia */

	char modo[1000];/** string pro numero ou modo */

	float a, b, sum, sub, divi, mult;/** variaveis utilizadas nos casos */

	float sum_total = 0, mult_total = 1, sub_total, copy, n;/** variaveis utilizadas nos casos */

	int c, i;/** contadores */

	scanf("%s", modo);/** input do modo */

	while(modo[0] != 'q'){/** q e o modo de saida */

		if(modo[0] == '+' && modo[1] != '!'){/* se for o operador + e nao for o operador +! caso */

			if(qnt_stack_float(top) < 2){/** verfica se tem operandos suficientes**/

				printf("Numero de Operandos insuficiente\n");
			}
			else {

				a	= pop_float(top);/** desempilha */

				b 	= pop_float(top);/** desempilha */

				sum = a + b;/** faz a soma */

				push_stack_float(sum, top);/** empilha o resultado */
			}

		}

		else if (modo[0] == '-' && modo[1] != '!'){/* se for o operador - e nao for o operador -! caso */

			if(qnt_stack_float(top) < 2){/** verfica se tem operandos suficientes**/

				printf("Numero de Operandos insuficiente\n");

			}
			else {

				a = pop_float(top);/** desempilha */

				b = pop_float(top);/** desempilha */

				sub = a - b;/** faz a diferença */

				push_stack_float(sub, top);/** empilha resultado */
			}
		}

		else if(modo[0] == '*' && modo[1] != '!'){/* se for o operador * e nao for o operador *! caso */

			if(qnt_stack_float(top) < 2){/** verfica se tem operandos suficientes**/

				printf("Numero de Operandos insuficiente\n");

			}
			else {

				a = pop_float(top);/** desempilha */

				b = pop_float(top);/** desempilha */

				mult = a * b;/** faz a multipilcação */

				push_stack_float(mult, top);/** empiha resultado */
			}

		}

		else if(modo[0] ==  '/'){/** se for divisão caso */

			if(qnt_stack_float(top) < 2){/** verifica se tem operandos suficientes */

				printf("Numero de Operandos insuficiente\n");

			}

			else {

				a = pop_float(top);/**desempilha */

				b = pop_float(top);/**desempilha */

				divi = a / b;/** faz a divisão */

				push_stack_float(divi, top);/** empilha resultado */
			}

		}

		else if(modo[0] == '+' && modo[1] == '!'){/** caso +! */

			if(qnt_stack_float(top) < 1){/** verifica se tem operandos suficientes */

				printf("Numero de Operandos insuficiente\n");

			}

			else {

				while(!is_empty_float(top)){/**enquanto não estiver vazia */

					a = pop_float(top);/** desempilha */

					sum_total += a;/** bota na soma total */

				}

				push_stack_float(sum_total, top);/** empilha resultado */

			}
		}

		else if(modo[0] == '-' && modo[1] == '!'){/** caso -!*/

			if(qnt_stack_float(top) < 1){/** verifica se tem operadores suficientes */

				printf("Numeros de Operandos insuficiente\n");

			}

			else {

				sub_total = pop_float(top);/**desempilha o primeiro valor */

				while(!is_empty_float(top)){/**enquanto nao for vazio */

					a = pop_float(top);/**desempilha */

					sub_total -= a;/**e joga no sub total */
				}

				push_stack_float(sub_total, top);/** empilha resultado */

			}
		}

		else if (modo[0] == '*' && modo[1] == '!'){/** caso *!*/

			if(qnt_stack_float(top) < 1){/** verifica se tem operadores suficientes */

				printf("Numeros de Operandos insuficiente\n");
			}

			else {

				while(!is_empty_float(top)){/** enquanto não estiver vazia */

					a = pop_float(top);/** desempilha */

					mult_total *= a;/**joga no mult */

				}

				push_stack_float(mult_total, top);/** empilha resultado */
			}
		}

		else if (modo[0] == 'c'){/** caso c */

			if(qnt_stack_float(top) < 2){/** verifica se tem operandos suficientes */

				printf("Numeros de Operandos insuficiente\n");
			}

			else {

				c = (int) pop_float(top);/**desempilha o numero de vezes pra copiar */

				copy = pop_float(top);/** desempilha o numero pra ser copiado */

				for(i = 0; i < c; i++){

					push_stack_float(copy, top);/** empilha esse numero c vezes */

				}
			}
		}

		else {/**caso for operando */

			n = string_to_float(modo);/**transforma string em float */

			push_stack_float(n,top);/** empilha*/
		}

		printf("\n\n\n");

		printf("------------Nova Pilha ----------------\n");

		print_stack_float(top);

		printf("\n\n\n\n");

		scanf("%s", modo);/** da input no novo modo */

	}
}

/**@brief a função qnt_stack_float() recebe um ponteiro pro top e conta quantos elementos tem nele  
*@param top 
*
*@return cont 
*/

int qnt_stack_float(stack_float *top){

	element_float *aux = top->tp;/** auxiliar pro topo */

	int cont = 0;/**contador */

	while(aux != NULL){/**enquanto não chegar no fim */

		cont++;/**conte */

		aux = aux->n;/**va para o proximo */
	}

	return cont;/** retorno a quantidade */
}
/**
/TO DO:Menu
*/

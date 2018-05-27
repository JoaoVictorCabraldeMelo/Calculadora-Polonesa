
/**
*@file calculator.h
*@author João Victor Cabral de Melo
*@date 14 May 2018
*@brief O programa foca em calcular expressões básicas pega elas infixas transforma em posfixas e calcula
*/

#ifndef __STACK_H__
#define __STACK_H__

/**@brief Estrutura do numero quando colocado na pilha
*/

typedef struct pointer{/**Estrutura com ponteiros para o proximo e guarda uma string numero */
												
	char expression;/**string do numero*/	

	struct pointer *next;/**ponteiro pro proximo*/

}element;/** numero na lista */

/**@brief Estrutura de ponteiro para o topo da lista 
*/

typedef struct {/** Estrutura para o topo da pilha */

	element *top;/** ponteiro pro topo */

}stack;/** pilha com ponteiro pro topo */

/**@brief Estrutura de pilha para um float 
*/

typedef struct ptr{/**estrutura com o proximo que guarda um float */

	float number;/** numero*/

	struct ptr *n;/**ponteiro pro proximo */

}element_float;/** numero na pilha */

/**@brief estrutura de pilha pro topo 
*/

typedef struct{/**estrutura para topo no float */

	element_float *tp;/** ponteiro pro topo */

}stack_float;/**novo nome pro ponteiro pro topo*/


/**@brief aloca um ponteiro para o topo da pilha
*@code 
*	pilha* top = (pilha *) malloc(sizeof(pilha));
*
*	top->topo = NULL;
*
*	return(top);
*	@endcode
 */ 
stack *alloc_stack();

/**@brief a função aloca numero na expressao
*@param a função recebe uma string como parametro
*@return number  
*/

element *alloc_number(char value);

/**@brief a função coloca numero na pilha
*@return void  
*/
void push_stack(char value, stack *top);

/**@brief a função printa a pilha na tela
*	@param top 
*@return void  
*/

void print_stack(stack *top);

/**@brief a funçao retorna True se a pilha estiver vazia
*  @param top 
*@return void  
*/

int is_empty(stack *top);

/**@brief a funçao retorna variable se a pilha não estiver vazia se estiver vazia então retorna '0' 
*  @param top 
*@return variable   
*/

char pop(stack *top);

/**@brief a funçao recebe um ponteiro pro topo e libera toda pilha  
*  @param top 
*@return void   
*/

void release_stack(stack *top);

/**
*	@brief a função catch_expression() recebe uma string e empilha toda ela  
*	@param1 top @param2 expression
* 	@return void
*/

void catch_expression(stack *top, char *expression);

/**
*	@brief a função verify_expression() recebe uma string e empilha os escopos de abertura se ele achar um escopo que fecha ele vai
*	desempilhar da pilha e vai verificar se e da familia do escopo no final ele verifica se a pilha não esta vazia se ela não estiver
*	os escopo não possui um escopo que fecha então a expressão e invalida    
*	@param1 expression
* 	@return bool
*/

int verify_expression(char *expression);

/**
*	@brief a função transform_in_sufix() recebe uma string expression ela aloca uma pilha caso ache uma abre parenteses ele empillha caso nao ache
*	um operando então ele vai colocar uma copia na string que vai sair da função caso ache um operando vai desempilha ate achar um escopo que abre     
*	@param1 expression
* 	@return expressão em sufixo
*/

char  *transform_in_sufix(char *expression);

/**@brief a função aloca uma pilha do tipo float
*@param void
*@return ponteiro pra pilha   
*/

stack_float *alloc_stack_float();

/**@brief a função aloca uma variavel do tipo float e seta na pilha
*@param void
*@return ponteiro pra o elemento_float  
*/

element_float *alloc_number_float(float value);

/**@brief a função push_stack_float() coloca numero na pilha
*@return void  
*/
void push_stack_float(float value, stack_float *top);

/**@brief a função print_stack_float() printa uma pilha de floats
*@param stack_float ponteiro pro topo
*@return void  
*/

void print_stack_float(stack_float *top);


/**@brief a função is_empty_float() verifica se a pilha esta vazia 
*@param ponteiro do stack_float pro topo
*@return int do tipo bool  
*/

int is_empty_float(stack_float *top);

/**@brief a função pop_float() desempilha pilha do tipo float 
*@param ponteiro do stack_float pro topo
*@return variable desempilhada 
*/

float pop_float(stack_float *top);

/**@brief a função release_stack_float() libera toda pilha 
*@param ponteiro do stack_float pro topo
*@return void
*/

void release_stack_float(stack_float *top);

/**@brief a função string_to_float() transforma a string a float  
*@param n 
*@return number 
*/

float string_to_float(char *n);

/**@brief a função catch_expression_float() a pega a expressão sufixa e faz os calculos na pilha deixando 
*	apenas com um resultado no final  
*@param ponteiro pro top de uma pilha de float @param string sufixa
*@return void
*/

void catch_expression_float(stack_float *top, char *expression);

void modo_calculadora();

int qnt_stack_float(stack_float *top);




#endif 
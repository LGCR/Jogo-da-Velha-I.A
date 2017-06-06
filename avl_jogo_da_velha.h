//
// Created by lucas on 25/05/17.
//

/*!
 * \file avl_jogo_da_velha.h
 * \brief É uma biblioteca para manipulação de AVL
 * \details Essa biblioteca para manipulação de uma AVL especial que guarda e gerência dados para
 * o funcionamento do jogo da velha.
 * \author Lucas Ribeiro
 * \date 25/05/2017
 * \headerfile stdio.h <>
 * \headerfile stdlib.h <>
 */

#ifndef JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H
#define JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H

#include <stdio.h>
#include <stdlib.h>

/*!
 * \struct struct node
 * \brief Essa estrutura representa um nó que irá formar a árvore AVL
 * \typedef typedef struct node {} No, Arvore;
 */
typedef struct node {
    int chave;          /*!< Variável inteira que armazena uma chave para reconhecer o nó*/
    int jogador;        /*!< Variável inteiro que armazena qual jogado fez a jogada*/
    int altura;         /*!< Variável inteiro que armazena a alteura do nó na árvore*/
    struct node* esq;   /*!< Ponteiro que aponta para o nó á esquerda do nó*/
    struct node* dir;   /*!< Ponteiro que aponta para o nó á direita do nó*/
} No, Arvore;

/*!
 * \fn int maior (int esq, int dir)
 * \brief Função que ao receber 2 inteiro, retorna o maior deles.
 * @param esq Inteiro que representa o valor a esquerda da AVL.
 * @param dir Inteiro que representa o valor a direita da AVL.
 * @return Retorno inteiro que representa o maior de ambos os valores.
 */
/*----------------------*/
int maior (int esq, int dir) ;

/*!
 * \fn int altura (Arvore* a)
 * \brief Função retorna a altura de uma árvore
 * \pre O ponteiro para a árvore não deve ter valor NULL
 * \warning Caso o pré requisito não seja atendito a funão retornará NULL
 * @param a Ponteiro que aponta para a árvore AVL.
 * @return Retorna um inteiro que representa
 */
/*----------------------*/
int altura (Arvore* a) ;

/*!
 * \fn int atualizar_altura(Arvore *a)
 * \brief Função recursiva que atualiza as altura da árvore.
 * @param a Ponteiro que aponta para o início da AVL
 * @return O retorno inteiro serve para o funcionamento da recursividade.
 */
int atualizar_altura(Arvore *a);

/*!
 * \fn int balanceamento (Arvore *a)
 * \brief Função que retorna a diferença das alturas do nós.
 * \details A função de balancemanto serve para retornar um valor que indica se o nó está
 * balanceado ou não, retornando um valor que vária de -2 a 2.
 * @param a Ponteiro que aponta para um nó da árvore AVL;
 * @return Retorna o valor do balanceamento
 */
/*----------------------*/
int balanceamento (Arvore *a) ;

/*!
 * \fn Arvore* rotacao_simples_esq (Arvore* r)
 * \brief Função que realiza uma rotação simples a esquerda na AVL.
 * @param r Ponteiro que aponta para um nó da árvore AVL!
 * @return Retorna o ponteiro do nó da AVL após a rotação feita
 */
/*----------------------*/
Arvore* rotacao_simples_esq (Arvore* r) ;

/*!
 * \fn Arvore* rotacao_simples_dir (Arvore* r)
 * \brief Função que realiza uma rotação simples a direita na AVL
 * @param r Ponteiro que aponta para um nó da árvore AVL.
 * @return Retorna o ponteiro do nó da AVL após a rotação feita
 */
/*----------------------*/
Arvore* rotacao_simples_dir (Arvore* r) ;

/*!
 * \fn Arvore* rotacao_dupla_esq (Arvore* r)
 * \brief Função que realiza uma rotação dupla a esquerda na AVL.
 * @param r Ponteiro que aponta para um nó da árvore AVL.
 * @return Retorna o ponteiro do nó da AVL após a rotação feita.
 */
/*----------------------*/
Arvore* rotacao_dupla_esq (Arvore* r) ;

/*!
 * \fn Arvore* rotacao_dupla_dir (Arvore* r)
 * \brief Função que realiza uma rotação dupla a direita na AVL.
 * @param r Ponteiro que aponta para um nó da árvore AVL.
 * @return Retorna o ponteiro do nó da AVL após a rotação feita.
 */
/*----------------------*/
Arvore* rotacao_dupla_dir (Arvore* r) ;

/*!
 * \fn Arvore* atualizar_fb_dir (Arvore *r)
 * \details Função que atualiza a altura e faz o balanceamento dos nós casos os dá direita estejam
 * desbalanceados.
 * @param r Ponteiro que aponta para um nó da árvore AVL.
 * @return Retorna o ponteiro para o nó após as devidas atualizações.
 */
/*----------------------*/
Arvore* atualizar_fb_dir (Arvore *r) ;

/*!
 * \fn Arvore* atualizar_fb_esq (Arvore *r)
 * \details Função que atualiza a altura e faz o balancemanto dos nós casos os daá esquerda estejam
 * desbalanceados.
 * @param r Ponteiro que aponta para um nó da árvore AVL.
 * @return Retorna o ponteiro para o nó após as devidas alterações feitas.
 */
/*----------------------*/
Arvore* atualizar_fb_esq (Arvore *r) ;

/*!
 * \fn Arvore* inserir (Arvore *a, int chave, int jogador)
 * \brief Insere um novo nó na ávore AVL.
 * @param a É um ponteiro que representa a árvore onde se quer inserir.
 * @param chave É um inteiro que representa o valor do nó.
 * @param jogador É um inteiro que representa o jogador que fez a jogada.
 * @return Retorna o ponteiro para árvore após a inserção ter sido feita.
 */
/*----------------------*/
Arvore* inserir (Arvore *a, int chave, int jogador);

/*!
 * \fn Arvore* remover (Arvore *a, int chave)
 * \brief Remove um nó da árvore AVL baseado na sua chave.
 * @param a É um ponteiro que aponta para a árvore ao qual se deseja remover o nó.
 * @param chave É um inteiro que representa a chave do nó que se pretende remover
 * @return Retorna o ponteiro para a árvore, após ter sido removido o nó.
 */
/*----------------------*/
Arvore* remover (Arvore *a, int chave);

/*!
 * \fn int buscar(Arvore *a, int chave)
 * \brief Função que encontra um nó específico baseado em sua chave e retorna o valor da variável
 * jogador.
 * @param a Ponteiro que aponta para a ávore em que se deseja buscar.
 * @param chave Inteiro que representa a chave do nó que se deseja achar.
 * @return Retorna um inteiro com o mesmo valor da variável jogador do nó que se buscava.
 */
int buscar(Arvore *a, int chave);

/*----------------------*/
void imprimir_in_order (Arvore* a, int nivel) ;

void arvore_para_vetor(Arvore* a, int *tabuleiro);

void imprimir_tabuleiro(Arvore* a);

/*!
 * \fn int verifica_ganhador(Arvore* a, int jogador)
 * \brief Essa função verifica se alguém ganhou o jogo e retorna um inteiro.
 * @param a É um ponteiro para a árvore AVL.
 * @param jogador É um inteiro que representa qual jogador se está verificando.
 * @return Inteiro de retorno
 */
int verifica_ganhador(Arvore* a, int jogador);

int conta_nos(Arvore *a);

void  calcula_passos(Arvore** verificacao, Arvore* a, Arvore* b, int *passos, int index);

Arvore* jogada_computador(Arvore* a, Arvore* verificacao);

int jogada_jogador();

int menu_principal();

#endif //JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H

//
// Created by lucas on 25/05/17.
//

#ifndef JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H
#define JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int chave;
    int jogador;
    int altura;
    struct node* esq;
    struct node* dir;
} No, Arvore;

void clear();

void flush();

/*----------------------*/
int maior (int esq, int dir) ;

/*----------------------*/
int altura (Arvore* a) ;

int atualizar_altura(Arvore *a);

/*----------------------*/
int balanceamento (Arvore *a) ;

/*----------------------*/
Arvore* rotacao_simples_esq (Arvore* r) ;

/*----------------------*/
Arvore* rotacao_simples_dir (Arvore* r) ;

/*----------------------*/
Arvore* rotacao_dupla_esq (Arvore* r) ;

/*----------------------*/
Arvore* rotacao_dupla_dir (Arvore* r) ;

/*----------------------*/
Arvore* atualizar_fb_dir (Arvore *r) ;

/*----------------------*/
Arvore* atualizar_fb_esq (Arvore *r) ;

/*----------------------*/
Arvore* inserir (Arvore *a, int chave, int jogador);

/*----------------------*/
Arvore* remover (Arvore *a, int chave);

int buscar(Arvore *a, int chave);

/*----------------------*/
void imprimir_in_order (Arvore* a, int nivel) ;

void arvore_para_vetor(Arvore* a, int *tabuleiro);

void imprimir_tabuleiro(Arvore* a);

int verifica_ganhador(Arvore* a, int jogador);

int conta_nos(Arvore *a);

void  calcula_passos(Arvore** verificacao, Arvore* a, Arvore* b, Arvore*c, int *passos, int index);

//void  calcula_passos(Arvore** verificacao, Arvore* a, Arvore* b, int *passos, int index);

Arvore* jogada_computador(Arvore* a, Arvore* verificacao, Arvore* ver_aux);

//Arvore* jogada_computador(Arvore* a, Arvore* verificacao);

int jogada_jogador();

int menu_principal();

#endif //JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H

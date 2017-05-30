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
    char jogada;
    int *tabuleiro;
    int pontos;
    int altura;
    struct node* esq;
    struct node* dir;
} No, Arvore;

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
Arvore* inserir (Arvore *a, int chave, char jogada, int *tabuleiro);

/*----------------------*/
Arvore* remover (Arvore *a, int chave);

/*----------------------*/
void imprimir_in_order (Arvore* a, int nivel) ;

void arvore_para_vetor(Arvore* a, int *tabuleiro);

void imprimir_tabuleiro(Arvore* a, int tabuleiro[]);

int verifica_ganhador(int jogador, int* tabuleiro);

int  calcula_passos(Arvore* a, int *tabuleiro, int passos, int index);

Arvore* jogada_computador(Arvore* a, int ultima_jogada);

int jogada_jogador();

int menu_principal();

#endif //JOGO_DA_VELHA_PROJETO_AVL_JOGO_DA_VELHA_H

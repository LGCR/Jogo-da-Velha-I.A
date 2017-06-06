//
// Created by lucas on 25/05/17.
//

/*!
 * \file avl_jogo_da_velha.c
 * \brief Implementação das funções descritas na biblioteca avl_jogo_da_velha.h
 * \author Lucas Ribeiro
 * \date 25/05/2017
 * \headerfile avl_jogo_da_velha.h ""
 */

#include "avl_jogo_da_velha.h"

void clear(){
  #ifdef __linux__
    system("clear");
  #elif defined _WIN32
    system("cls");
  #else
    perror("Plataforma não suportada");
  #endif
}

/*----------------------*/
int maior (int esq, int dir) {
   return (esq > dir ? esq : dir);
}

/*----------------------*/
int altura (Arvore* a) {
   if (a == NULL) {
      return -1;
   }
   else {
      return a->altura;
   }
}

int atualizar_altura(Arvore *a){
	int altura_direita = 0;
    int altura_esquerda = 0;
    if((a != NULL)) {
        if(a->dir == NULL && a->esq == NULL){
            return a->altura + 1;
        }
        else{
            if(a->dir != NULL)
                altura_direita = a->dir->altura;
            if(a->esq != NULL)
                altura_esquerda = a->esq->altura;
            
            if(maior(altura_esquerda, altura_direita) == altura_esquerda){
                atualizar_altura(a->esq);
                return altura_esquerda + 1;
            }
            else{
                atualizar_altura(a->dir);
                return altura_direita + 1;
            }
        }
    }
    return 0;
}

/*----------------------*/
int balanceamento (Arvore *a) {
   return (altura(a->dir) - altura(a->esq));
}

/*----------------------*/
Arvore* rotacao_simples_esq (Arvore* r) {
   No *t = r->dir;
   r->dir = t->esq;
   t->esq = r;
   r->altura = atualizar_altura(r);
   t->altura = atualizar_altura(t);
   return t;
}

/*----------------------*/
Arvore* rotacao_simples_dir (Arvore* r) {
    No *t = r->esq;
    r->esq = t->dir;
    t->dir = r;
    r->altura = atualizar_altura(r);
    t->altura = atualizar_altura(t);
    return t;
}

/*----------------------*/
Arvore* rotacao_dupla_esq (Arvore* r) {
   r->dir = rotacao_simples_dir(r->dir);
   return rotacao_simples_esq(r);
}

/*----------------------*/
Arvore* rotacao_dupla_dir (Arvore* r) {
    r->esq = rotacao_simples_esq(r->esq);
    return rotacao_simples_dir(r);
}

/*----------------------*/
Arvore* atualizar_fb_dir (Arvore *r) {
   r->altura = atualizar_altura(r); 
   if (balanceamento(r) == +2) {
       if(balanceamento(r->dir) >= 0){
           r = rotacao_simples_esq(r);
       }
       else
       {
           r = rotacao_dupla_esq(r);
       }
   }
   return r;
}

/*----------------------*/
Arvore* atualizar_fb_esq (Arvore *r) {
   r->altura = atualizar_altura(r); 
   if (balanceamento(r) == -2) {
       if(balanceamento(r->esq) <= 0){
           r = rotacao_simples_dir(r);
       }
       else
       {
           r = rotacao_dupla_dir(r);
       }
   }
   return r;
}

/*----------------------*/
Arvore* inserir (Arvore *a, int chave, int jogador) {
   if (a == NULL) {
      a = (No*)malloc(sizeof(No));
      a->chave = chave;
      a->altura = 0;
      a->esq = a->dir = NULL;
      a->jogador = jogador;
   }
   else if (chave < a->chave) {
      a->esq = inserir (a->esq, chave, jogador);
      a = atualizar_fb_esq (a);
   }
   else if (chave > a->chave) {
      a->dir = inserir (a->dir, chave, jogador);
      a = atualizar_fb_dir (a);
   }
   return a;
}

/*----------------------*/
Arvore* remover (Arvore *a, int chave) {
   if (a == NULL) {
      return NULL;
   }
   else {
      if (chave < a->chave) {
         a->esq = remover (a->esq, chave);
         a = atualizar_fb_dir (a);
      }
      else if (chave > a->chave) {
         a->dir = remover (a->dir, chave);
         a = atualizar_fb_esq (a);
      }
      else {
         if ((a->esq == NULL) && (a->dir == NULL)) {
            free (a);
            a = NULL;
         }
         else if (a->esq == NULL) {
            No *tmp = a;
            a = a->dir;
            free (tmp);
         }
         else if (a->dir == NULL) {
            No *tmp = a;
            a = a->esq;
            free (tmp);
         }
         else {
            No *tmp = a->esq;
            while (tmp->dir != NULL) {
               tmp = tmp->dir;
            }
            a->chave = tmp->chave; 
            tmp->chave = chave;
            a->esq = remover (a->esq, chave); 
            a = atualizar_fb_dir (a);
         }
      }
      return a; 
   }   
}

int buscar(Arvore *a, int chave){
    int jogador = 0;
    if(a != NULL){
        if(chave == a->chave){
            return a->jogador;
        }
        else if(chave < a->chave){
            return buscar(a->esq, chave);
        }
        else{
            return buscar(a->dir, chave);
        }
    }
    return jogador;
}

/*----------------------*/
void imprimir_in_order (Arvore* a, int nivel) {
   if (a != NULL) {
      int i;
      for (i = 0; i < nivel; i++) {
         printf("      ");
      }
      printf("Chave: %d (fb: %+d) no nível: %d\n", a->chave, balanceamento(a), nivel);
      imprimir_in_order (a->esq, nivel + 1);
      imprimir_in_order (a->dir, nivel + 1);
   }
}

void arvore_para_vetor(Arvore* a, int *tabuleiro){
    if(a != NULL){
        tabuleiro[a->chave] = a->jogador;
        arvore_para_vetor(a->esq, tabuleiro);
        arvore_para_vetor(a->dir, tabuleiro);
    }
}

void imprimir_tabuleiro(Arvore* a){
    int i, tabuleiro[] = {0,0,0,0,0,0,0,0,0};
    char jogada;

    if(a != NULL) {
        arvore_para_vetor(a, tabuleiro);
    }

    //flush();
    printf("\n");
    for (i = 0; i < 9; ++i) {
        if(tabuleiro[i] == 1){
            jogada = 'X';
        } else if(tabuleiro[i] == 2){
            jogada = 'O';
        } else{
            jogada = ' ';
        }
        printf("  %c  ", jogada);
        if(i == 2 || i == 5 || i == 8){
            if(i != 8){
                printf("\n------------------\n");
            }
            if(i == 8){
                printf("\n\n");
            }
        }
        else{
            printf("|");
        }
    }
}

int verifica_ganhador(Arvore* a, int jogador){
    if(a != NULL){
        if((buscar(a, 0) == jogador) && (buscar(a, 1) == jogador) && (buscar(a, 2) == jogador)){
            return 0;
        }
        else if((buscar(a, 0) == jogador) && (buscar(a, 3) == jogador) && (buscar(a, 6) == jogador)){
            return 1;
        }
        else if((buscar(a, 0) == jogador) && (buscar(a, 4) == jogador) && (buscar(a, 8) == jogador)){
            return 2;
        }
        else if((buscar(a, 1) == jogador) && (buscar(a, 4) == jogador) && (buscar(a, 7) == jogador)){
            return 3;
        }
        else if((buscar(a, 2) == jogador) && (buscar(a, 4) == jogador) && (buscar(a, 6) == jogador)){
            return 4;
        }
        else if((buscar(a, 2) == jogador) && (buscar(a, 5) == jogador) && (buscar(a, 8) == jogador)){
            return 5;
        }
        else if((buscar(a, 3) == jogador) && (buscar(a, 4) == jogador) && (buscar(a, 5) == jogador)){
            return 6;
        }
        else if((buscar(a, 6) == jogador) && (buscar(a, 7) == jogador) && (buscar(a, 8) == jogador)){
            return 7;
        }
    }
    return -1;
}

int conta_nos(Arvore *a){
    if(a != NULL){
        return 1 + conta_nos(a->esq) + conta_nos(a->dir);
    }
    return 0;
}

void  calcula_passos(Arvore** verificacao, Arvore* a, Arvore* b, int *passos, int index){
    if(index < 9) {
        if (*verificacao != NULL) {
            if (buscar(a, index) == 0) {
                *verificacao = inserir(*verificacao, index, 1);
                if (verifica_ganhador(b, 1) == -1) {
                    calcula_passos(&(*verificacao)->esq, a, b, passos, index + 1);
                    calcula_passos(&(*verificacao)->dir, a, b, passos, index + 1);
                }
                if(verifica_ganhador(b, 1) != -1){
                    a = inserir(a, index, 1);
                    if(verifica_ganhador(a, 1) != -1) {
                        *passos = index;
                    }
                    a = remover(a, index);
                    if (*passos == 0){
                        if(buscar(a, 0) == 0){
                            *passos = 0;
                        }
                        else if(buscar(a, 2) == 0){
                            *passos = 2;
                        }
                        else if(buscar(a, 6) == 0){
                            *passos = 6;
                        }
                        else if(buscar(a, 8) == 0){
                            *passos = 8;
                        }
                        else if(buscar(a, 4) == 0){
                            *passos = 4;
                        }
                        else if(buscar(a, 1) == 0){
                            *passos = 1;
                        }
                        else if(buscar(a, 3) == 0){
                            *passos = 3;
                        }
                        else if(buscar(a, 5) == 0){
                            *passos = 5;
                        }
                        else if(buscar(a, 7) == 0){
                            *passos = 7;
                        }
                    }
                }
                *verificacao = remover(*verificacao, index);
            } else{
                calcula_passos(&(*verificacao), a, b, passos, index + 1);
            }
        }
    }
}

Arvore* jogada_computador(Arvore* a, Arvore* verificacao){

    int i, modo = 1, passos = 0, index = 0;

    if(a != NULL){
        for (i = 0; i < 9; ++i) {
            if (buscar(a, i) == 0) {
                calcula_passos(&verificacao, a, verificacao, &passos, i);
                index = passos;
            }
        }
        a = inserir(a, index, 2);
        verificacao = inserir(verificacao, index, 2);
    }
    return a;
}

int jogada_jogador(){
    int opcao = -2;
    while(opcao < -1 || opcao > 8) {
        printf("\nDigite uma posição [0-8]\n> ");
        scanf("%d", &opcao);
    }
    return opcao;
}

int menu_principal(){
  char opcoes_menu[3][35] = {"1 - Jogar contra o computador", "2 - Jogar contra outro jogador", "3 - Sair"};
  int i, j, opcao;

  clear();
  printf("=================================\n");
  for (i = 0; i < 3; ++i){
    for (j = 0; j < 35; ++j){
        if(opcoes_menu[i][j] != '\0') {
            printf("%c", opcoes_menu[i][j]);
        }
        else{
        printf("\n");
        break;
      }
    }
  }
  printf("=================================\n> ");
  scanf("%d", &opcao);
  return opcao;
}
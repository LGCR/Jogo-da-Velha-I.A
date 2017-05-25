//
// Created by lucas on 25/05/17.
//


#include "avl_jogo_da_velha.h"

void flush()
{
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
	int altura_direita;
    int altura_esquerda;
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
    r->esq = rotacao_simples_dir(r->esq);
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
Arvore* inserir (Arvore *a, int chave, char jogada, int *tabuleiro) {
   if (a == NULL) {
      a = (No*)malloc(sizeof(No));
      a->chave = chave;
      a->jogada = jogada;
      a->altura = 0;
      a->tabuleiro = tabuleiro;
      a->esq = a->dir = NULL;
      if(jogada == 'X'){
          a->jogador = 1;
          a->pontos = 10;
      }
      else if(jogada == 'O'){
          a->jogador = 2;
          a->pontos = -10;
      }
      else{
          a->jogador = 0;
      }
      a->tabuleiro[a->chave] = a->jogador;
   }
   else if (chave < a->chave) {
      a->esq = inserir (a->esq, chave, jogada, tabuleiro);
      a = atualizar_fb_esq (a);
   }
   else if (chave > a->chave) {
      a->dir = inserir (a->dir, chave, jogada, tabuleiro);
      a = atualizar_fb_dir (a);
   }
   else{
       printf("\nJogada Inválida!\n");
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

void imprimir_tabuleiro(Arvore* a, int tabuleiro[]){
    int i;
    char jogada;

    arvore_para_vetor(a, tabuleiro);

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

int verifica_ganhador(int jogador, int* tabuleiro){
    if((tabuleiro[0] == jogador) && (tabuleiro[1] == jogador) && (tabuleiro[2] == jogador)){
        return 0;
    }
    else if((tabuleiro[0] == jogador) && (tabuleiro[3] == jogador) && (tabuleiro[6] == jogador)){
        return 1;
    }
    else if((tabuleiro[0] == jogador) && (tabuleiro[4] == jogador) && (tabuleiro[8] == jogador)){
        return 2;
    }
    else if((tabuleiro[1] == jogador) && (tabuleiro[4] == jogador) && (tabuleiro[7] == jogador)){
        return 3;
    }
    else if((tabuleiro[2] == jogador) && (tabuleiro[4] == jogador) && (tabuleiro[6] == jogador)){
        return 4;
    }
    else if((tabuleiro[2] == jogador) && (tabuleiro[5] == jogador) && (tabuleiro[8] == jogador)){
        return 5;
    }
    else if((tabuleiro[3] == jogador) && (tabuleiro[4] == jogador) && (tabuleiro[5] == jogador)){
        return 6;
    }
    else if((tabuleiro[6] == jogador) && (tabuleiro[7] == jogador) && (tabuleiro[8] == jogador)){
        return 7;
    }
    else{
        return -1;
    }
}

int  calcula_passos(Arvore* a, int *tabuleiro, int passos, int index){
    if(index < 9) {
        if (tabuleiro[index] == 0) {
            a = inserir(a, index, 'X', tabuleiro);
            if (verifica_ganhador(1, tabuleiro) == -1) {
                passos = calcula_passos(a, tabuleiro, (passos) + 1, index + 1);
            }
            if (verifica_ganhador(1, tabuleiro) != -1) {
                tabuleiro[index] = 2;
            }
        } else {
            passos = calcula_passos(a, tabuleiro, passos + 1, index + 1);
        }
    }
    return passos;
}

Arvore* jogada_computador(Arvore* a, int ultima_jogada){

    int i, j, index = 0, passos, menor = 100;
    int tab_aux[9];

    for (i = 0; i < 9; ++i) {
        tab_aux[i] = a->tabuleiro[i];
    }

    if(a != NULL) {
        if(ultima_jogada == a->chave){
            for (i = 0; i < 9; ++i){
                if(i != a->chave && a->tabuleiro[i] != 1 && a->tabuleiro[i] != 2) {
                    Arvore* aux= NULL;
                    passos = calcula_passos(aux, tab_aux, 0, i);
                    if(passos < menor){
                        menor = passos;
                        i = i + menor;
                        index = i;
                        tab_aux[index] = 2;
                    }
                    else if(passos == menor && index < i){
                        //--menor;
                        for(j = index; j <= i + passos; ++j){
                            if(a->tabuleiro[j] == 0){
                                a->tabuleiro[j] = 1;
                                if(verifica_ganhador(1, a->tabuleiro) != -1){
                                    index = j;
                                }
				a->tabuleiro[j] = 0;
                            }
                        }
                    }
                }
            }
            a = inserir(a, index, 'O', a->tabuleiro);
        }
        else {
            if (ultima_jogada < a->chave) {
                jogada_computador(a->esq, ultima_jogada);
            }
            if (ultima_jogada > a->chave) {
                jogada_computador(a->dir, ultima_jogada);
            }
        }
    }
    return a;
}

int jogada_jogador(){
    int opcao = -1;
    while(opcao < 0 || opcao > 8) {
        printf("\nDigite uma posição [0-8]\n> ");
        scanf("%d", &opcao);
    }
    return opcao;
}

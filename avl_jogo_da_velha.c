//
// Created by lucas on 25/05/17.
//


#include <stdio_ext.h>
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

void flush(){
#ifdef __linux__
    __fpurge(stdin);
#elif defined _WIN32
    fflsuh(stdin);
  #else
    perror("Plataforma não suportada");
#endif
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
        /*else{
            jogador = buscar(a->esq, chave);
            if(jogador == 0){
                jogador = buscar(a->dir, chave);
            }
        }*/
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
        tabuleiro[a->chave] = a->jogador; //Insere chave no vetor
        arvore_para_vetor(a->esq, tabuleiro); //Percorre Arvore
        arvore_para_vetor(a->dir, tabuleiro); //Percorre Arvore
    }
}

void imprimir_tabuleiro(Arvore* a){
    int i, tabuleiro[] = {0,0,0,0,0,0,0,0,0};
    char jogada;

    if(a != NULL) {
        arvore_para_vetor(a, tabuleiro); //Transforma Avl em vetor
    }

    //flush();
    printf("\n");
    for (i = 0; i < 9; ++i) {
        if(tabuleiro[i] == 1){ //Se Jogador X
            jogada = 'X';
        } else if(tabuleiro[i] == 2){ //Se jogador O
            jogada = 'O';
        } else{ //Espaço em branco
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

//void  calcula_passos(Arvore** verificacao, Arvore* a, Arvore* b, Arvore* c, int *passos, int index){

void  calcula_passos(Arvore** verificacao, Arvore* a, Arvore* b, Arvore* c, int *passos, int index){
    if(index < 9) {
        if (*verificacao != NULL) { //Se não for vazia
            if (buscar(a, index) == 0) { //Se indice for vazio na arvore
                if (buscar(*verificacao, index) == 0) { //Se for vazio na arvore de verificacao tambem
                    *verificacao = inserir(*verificacao, index, 1); //Insere na arvore de verificação
                    if (verifica_ganhador(b, 1) == -1) { //Verfica se foi possivel ganhar com o indice inserido
                        calcula_passos(&(*verificacao)->esq, a, b, c, passos, index + 1); //Percorre Arvore
                        calcula_passos(&(*verificacao)->dir, a, b, c, passos, index + 1); //Percorre Arvore
                    }
                    if (verifica_ganhador(b, 1) != -1) { //Se for possível X ganhar
                        if(buscar(c, index) == 0) {
                            c = inserir(c, index, 1);
                            if (verifica_ganhador(c, 1) != -1) {
                                *passos = index;
                            }
                            c = remover(c, index);
                        }
                    }
                    if (*passos == 0) { //Tenta outras jogadas
                        if (buscar(a, 0) == 0) { //Tenta nos cantos superiores
                            *passos = 0;
                        } else if (buscar(a, 2) == 0) { //Tenta nos cantos superiores
                            *passos = 2;
                        } else if (buscar(a, 6) == 0) { //Tenta nos cantos inferiores
                            *passos = 6;
                        } else if (buscar(a, 8) == 0) { //Tenta nos cantos inferiores
                            *passos = 8;
                        } else if (buscar(a, 4) == 0) { //Tenta no centro
                            *passos = 4;
                        } else if (buscar(a, 1) == 0) { //Tenta no centro superior
                            *passos = 1;
                        } else if (buscar(a, 3) == 0) { //Tenta no centro lateral
                            *passos = 3;
                        } else if (buscar(a, 5) == 0) { //Tenta no centro lateral
                            *passos = 5;
                        } else if (buscar(a, 7) == 0) { //Tenta no centro inferior
                            *passos = 7;
                        }
                    }
                    *verificacao = remover(*verificacao, index); //Remove da arvore de verificação
                } else { //Se já houver indice na arvore
                    calcula_passos(&(*verificacao), a, b, c, passos, index + 1); //Percorre arvore
                }
            }
        }
    }
}

Arvore* jogada_computador(Arvore* a, Arvore* verificacao, Arvore* ver_aux){

    int i, modo = 1, passos = 0, index = -1;

    if(a != NULL){ //Se não for vazia
        for(i = 0; i < 9; ++i){ //Laço
            if(buscar(verificacao, i) == 0){ //verifica existe indice na arvore
                verificacao = inserir(verificacao, i, 2); //Insere na arvore de verificacao
                if(verifica_ganhador(verificacao, 2) != -1){ //Verfica se foi possivel 'O' ganhar
                    ver_aux = inserir(ver_aux, i, 2);//Insere indice na arvore real
                    if(verifica_ganhador(ver_aux, 2) != -1) { //Verfica se foi possivel 'O' ganhar na arvore real
                        index = i; //index = 1
                        break; //Sai do laço
                    }
                    ver_aux = remover(ver_aux, i); //remove da arvore real se não ganhar
                }
                verificacao = remover(verificacao, i); //remove da arvore de verificação
            }
        }
        if(index == -1) { //Se não foi possivel ganhar
            for (i = 0; i < 9; ++i) {
                if (buscar(a, i) == 0) { //busca se existe na arvore
                    calcula_passos(&verificacao, a, verificacao, ver_aux, &passos, i); //Calcula possibilidades pra se defender
                    index = passos; //index = passos, indice a ser inserido na arvore
                }
            }
            a = inserir(a, index, 2);//insere na arvore real
            verificacao = inserir(verificacao, index, 2); // insere na avore de verificação
            ver_aux = inserir(ver_aux, index, 2);
        }
    }
    return a; //retorna arvore
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
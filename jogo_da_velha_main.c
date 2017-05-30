//
// Created by lucas on 25/05/17.
//

#include <stdbool.h>
#include "avl_jogo_da_velha.h"

void jogar_contra_computador(int *tabuleiro, Arvore *a){
    int opcao = 0, jogador = 1, jogador_anterior = 2, vezes = 0, aux = 0; //Variáveis locais de verificação
    while (true) { //Enquanto o jogo não terminar será verdadeiro
        imprimir_tabuleiro(a, tabuleiro); //Imprime tabuleiro na tela
        if(vezes == 9){ //Se for igual a 10 o jogo deu velha
            printf("\nDeu Velha!\n"); //Imprime na tela
            break; //Sai do laço
        }
        if(verifica_ganhador(jogador, tabuleiro) != -1){ //Se retorno da verificação for diferente de -1 e jogador igual a 1, jogador ganhou
            if(jogador == 1) { // Se Jogador 'X'
                printf("\nParabéns! Você ganhou!\n"); //Imprime na tela
                break; //Sai do laço
            }
            else { //Se jogador 'O'
                printf("\nQue pena! Você perdeu!\n"); //Imprime na tela
                break; //Sai do laço
            }
        }

        //Realização de swap entre jogadores
        if(vezes > 0) { //Se vezes for maior que 0
            aux = jogador; //Guarda em aux o valor de jogador
            jogador = jogador_anterior; //jogador recebe jogador_anterior
            jogador_anterior = aux; //jogador_anterior recebe o valor de aux que contem o valor anterior de jogador
        }

        if(jogador == 1) { //Ações do jogador
            opcao = jogada_jogador(); // Jogador escolhe uma posição
            a = inserir(a, opcao, 'X', tabuleiro); //Insere na Árvore
        }else { //Ações do computador
            a = jogada_computador(a, opcao); //Computador faz sua jogada
        }
        ++vezes; //Incrementa o número de vezes jogadas
    }
}

/*-----------------------*/
void jogar_contra_jogador(int* tabuleiro, Arvore *a){
    int opcao = 0, jogador = 1, jogador_anterior = 2, vezes = 0, aux = 0; //Variáveis locais de verificação
    while (true) { //Enquanto o jogo não terminar será verdadeiro
        imprimir_tabuleiro(a, tabuleiro); //Imprime tabuleiro na tela
        if(vezes == 9){ //Se for igual a 10 o jogo deu velha
            printf("\nDeu Velha!\n"); //Imprime na tela
            break; //Sai do laço
        }
        if(verifica_ganhador(jogador, tabuleiro) != -1){ //Se retorno da verificação for diferente de -1 e jogador igual a 1, jogador ganhou
            if(jogador == 1) { // Se Jogador 'X'
                printf("\nParabéns! Você ganhou!\n"); //Imprime na tela
                break; //Sai do laço
            }
            else { //Se jogador 'O'
                printf("\nQue pena! Você perdeu!\n"); //Imprime na tela
                break; //Sai do laço
            }
        }

        //Realização de swap entre jogadores
        if(vezes > 0) { //Se vezes for maior que 0
            aux = jogador; //Guarda em aux o valor de jogador
            jogador = jogador_anterior; //jogador recebe jogador_anterior
            jogador_anterior = aux; //jogador_anterior recebe o valor de aux que contem o valor anterior de jogador
        }
        if(jogador == 1) { //Ações do jogador 'X'
            opcao = jogada_jogador(); // Jogador escolhe uma posição
            a = inserir(a, opcao, 'X', tabuleiro); //Insere na Árvore
        }else { //Ações do jogador 'O'
            opcao = jogada_jogador(); // Jogador escolhe uma posição
            a = inserir(a, opcao, 'O', tabuleiro); //Insere na Árvore
        }
        ++vezes; //Incrementa o número de vezes jogadas
    }
}

/*----------------------*/
int main () {

    int tabuleiro[] = {0,0,0,0,0,0,0,0,0};
    Arvore *AVL = NULL;
    int opcao = 0, i;

    while(opcao != 5){
        for (i = 0; i < 9; ++i) {
            tabuleiro[i] = 0;
        }
        opcao = menu_principal();
        switch (opcao){
            case 1:
                jogar_contra_computador(tabuleiro, AVL);
                break;
            case 2:
                jogar_contra_jogador(tabuleiro, AVL);
                break;
            case 5:
                exit(0);
        }
    }

    return 0;
}


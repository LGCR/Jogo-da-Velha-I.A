//
// Created by lucas on 25/05/17.
//

#include "avl_jogo_da_velha.h"

/*----------------------*/
int main () {

    int tabuleiro[] = {0,0,0,0,0,0,0,0,0};
    Arvore *AVL = NULL;
    int opcao, jogador1 = 1, jogador2 = 2;

    while(1){
        opcao = jogada_jogador();
        AVL = inserir(AVL, opcao, 'X', tabuleiro);
        imprimir_tabuleiro(AVL, tabuleiro);
        if(verifica_ganhador(jogador1, tabuleiro) != -1){
            printf("\nParabéns! Você ganhou!\n");
            break;
        }
        else {
            AVL = jogada_computador(AVL, opcao);
            imprimir_tabuleiro(AVL, tabuleiro);
            if(verifica_ganhador(jogador2, tabuleiro) != -1){
                printf("\nQue pena! Você perdeu!\n");
                break;
            }
        }
    }

    return 0;
}


//
// Created by lucas on 25/05/17.
//

#include <stdbool.h>
#include "avl_jogo_da_velha.h"

void jogar_contra_computador(Arvore *a){
    int nos = 0, opcao = 0, jogador = 1, jogador_anterior = 2, vezes = 0, aux = 0; //Variáveis locais de verificação
    Arvore* verificacao = NULL;
    while (true) { //Enquanto o jogo não terminar será verdadeiro
        if(nos != -1) {
            nos = conta_nos(a);
        } else{
            break;
        }
        imprimir_tabuleiro(a); //Imprime tabuleiro na tela
        if(vezes == 9){ //Se for igual a 10 o jogo deu velha
            printf("\nDeu Velha!\n"); //Imprime na tela
            break; //Sai do laço
        }
        if(verifica_ganhador(a, jogador) != -1){ //Se retorno da verificação for diferente de -1 e jogador igual a 1, jogador ganhou
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
            while (nos == conta_nos(a)) {
                opcao = jogada_jogador(); // Jogador escolhe uma posição
                if(opcao == -1){
                    nos = -1;
                }
                else if(buscar(a, opcao) == 0) {
                    a = inserir(a, opcao, 1); //Insere na Árvore
                    verificacao = inserir(verificacao, opcao, 1);
                }
            }
        }else { //Ações do computador
            a = jogada_computador(a, verificacao); //Computador faz sua jogada
        }
        ++vezes; //Incrementa o número de vezes jogadas
    }
}

/*-----------------------*/
void jogar_contra_jogador(Arvore *a){
    int opcao = 0, nos = 0, jogador = 1, jogador_anterior = 2, vezes = 0, aux = 0; //Variáveis locais de verificação
    while (true) { //Enquanto o jogo não terminar será verdadeiro
        if(nos != -1) {
            nos = conta_nos(a);
        } else{
            break;
        }
        imprimir_tabuleiro(a); //Imprime tabuleiro na tela
        if(vezes == 9){ //Se for igual a 10 o jogo deu velha
            printf("\nDeu Velha!\n"); //Imprime na tela
            break; //Sai do laço
        }
        if(verifica_ganhador(a, jogador) != -1){ //Se retorno da verificação for diferente de -1 e jogador igual a 1, jogador ganhou
            if(jogador == 1) { // Se Jogador 'X'
                printf("\nParabéns! O jogador 'X' ganhou!\n"); //Imprime na tela
                break; //Sai do laço
            }
            else { //Se jogador 'O'
                printf("\nQue pena! O jogador 'O' perdeu!\n"); //Imprime na tela
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
            while (nos == conta_nos(a)) {
                opcao = jogada_jogador(); // Jogador escolhe uma posição
                if(opcao == -1){
                    nos = -1;
                }
                else if(buscar(a, opcao) == 0) {
                    a = inserir(a, opcao, 1); //Insere na Árvore
                }
            }
        }else { //Ações do jogador 'O'
            while (nos == conta_nos(a)) {
                opcao = jogada_jogador(); // Jogador escolhe uma posição
                if(opcao == -1){
                    nos = -1;
                }
                else if(buscar(a, opcao) == 0) {
                    a = inserir(a, opcao, 2); //Insere na Árvore
                }
            }
        }
        ++vezes; //Incrementa o número de vezes jogadas
    }
}

/*----------------------*/
int main () {

    Arvore *AVL = NULL;
    int opcao = 0, i;

    while(opcao != 5){
        opcao = menu_principal();
        switch (opcao){
            case 1:
                jogar_contra_computador(AVL);
                break;
            case 2:
                jogar_contra_jogador(AVL);
                break;
            case 3:
                exit(0);
        }
    }

    return 0;
}


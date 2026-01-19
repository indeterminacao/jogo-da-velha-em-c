#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(){
    LimpaTerminal();
    Partidas *historico = NULL;
    int x, y, partidas = 0, lances = 0, jogo = 1, velha = 1, QuemVai = 1; 
    char res;
    char tab[3][3];

    printf("### JOGO DA VELHA ###\n");
    printf("Jogador 1 = X | Jogador 2 = O\n");
    printf("A ordem de quem comeca inverte a cada partida.\n\n");
    printf("Pressione Enter para comecar...");

    while(getchar() != '\n') {
    }
    LimpaTerminal();

    while(velha == 1){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                tab[i][j] = '-';
            }
        }

        jogo = 1;
        lances = 0;
        int jogador_atual = QuemVai;

        while(jogo == 1){
            LimpaTerminal();
            estrutura(tab);

            char simbolo_vez;
            if (jogador_atual == 1) {
                simbolo_vez = 'X';
            } else {
                simbolo_vez = 'O';
            }

            printf("Vez do Jogador %d (%c)\n", jogador_atual, simbolo_vez);
            printf("Diga a coordenada (linha coluna): ");
            
            if (scanf("%d %d", &x, &y) != 2) {
                while(getchar() != '\n') {
                }
                x = 0; 
                y = 0;
            }

            int valida = jogada(tab, x, y);

            if(valida == 1){
                tab[x-1][y-1] = simbolo_vez;
                lances++;
                res = vitoria(tab, x, y, lances);
                if(res != 0){
                    jogo = 0;
                    LimpaTerminal();
                    estrutura(tab);
                } else {
                    if (jogador_atual == 1) {
                        jogador_atual = 2;
                    } else {
                        jogador_atual = 1;
                    }
                }
                
            } else if(valida == -1){
                printf("\n>>> ERRO: COORDENADA INVALIDA! Use 1 a 3. <<<\n");
                printf("Pressione Enter para tentar de novo...");
                while(getchar() != '\n') { } 
                getchar(); 
                
            } else if(valida == -2){
                printf("\n>>> ERRO: POSICAO JA PREENCHIDA. <<<\n");
                printf("Pressione Enter para tentar de novo...");
                while(getchar() != '\n') { }
                getchar(); 
            }
        }

        partidas++; 
        Partidas *temporaria = realloc(historico, partidas * sizeof(Partidas));

        if (temporaria == NULL) {
            printf("Erro de memoria!\n");
            free(historico);
            return 1;
        } else {
            historico = temporaria;
        }

        historico[partidas-1].resultado = res;
        historico[partidas-1].jogadas = lances;
        
        if (res == 1) {
            historico[partidas-1].simbolo = 'X';
        } else if (res == 2) {
            historico[partidas-1].simbolo = 'O';
        } else {
            historico[partidas-1].simbolo = '-';
        }

        if (res == 3) {
            historico[partidas-1].empates = 1;
            printf("\nDEU VELHA!\n");
        } else {
            historico[partidas-1].empates = 0;
            printf("\nVitoria do Jogador %d (%c)\n", historico[partidas-1].resultado, historico[partidas-1].simbolo);
        }

        if (QuemVai == 1) {
            QuemVai = 2;
        } else {
            QuemVai = 1;
        }

        printf("\nDeseja jogar novamente? (1-Sim / 0-Nao): ");
        int opcao;
        scanf("%d", &opcao);
        while(getchar() != '\n') {
        }
        
        if(opcao == 0){
            velha = 0;
        } else {
            LimpaTerminal();
        }
    }
    
    LimpaTerminal();
    printf("--- ESTATISTICAS ---\n");
    for(int i = 0; i < partidas; i++){
        printf("Partida %d: ", i+1);
        if(historico[i].resultado == 3) {
            printf("Empate");
        } else {
            printf("Vitoria do Jogador %d (%c)", historico[i].resultado, historico[i].simbolo);
        }
        printf(" (%d jogadas)\n", historico[i].jogadas);
    }

    printf("\n\nPressione qualquer tecla para fechar...");
    getchar();

    free(historico);
    return 0;
}
#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>

void LimpaTerminal(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void estrutura(char (*tab)[3]){
    printf("     1   2   3\n");
    printf("\n");

    for (int i = 0; i < 3; i++){
        printf(" %d  ", i + 1);
        for (int j = 0; j < 3; j++){
            printf(" %c ", tab[i][j]);
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
        if (i < 2){
            printf("    ---+---+---\n");
        }
    }
    printf("\n");
}

void renderizacao(char (*mapa)[3], char simbolo, int x, int y){
    mapa[x - 1][y - 1] = simbolo;
    LimpaTerminal();
    estrutura(mapa);
}

int jogada(char (*mapa)[3], int x, int y){
    if ((x >= 1 && x <= 3) && (y >= 1 && y <= 3)) {
        if (mapa[x - 1][y - 1] == '-'){
            return 1;
        } else {
            return -2;
        }
    } else {
        return -1;
    }
}

int vitoria(char (*tab)[3], int x, int y, int lance){
    if (lance < 4){
        return 0;
    } 
    x--;
    y--;

    char atual = tab[x][y];

    if (atual == '-') {
        return 0;
    }


    if (tab[x][0] == atual && tab[x][1] == atual && tab[x][2] == atual){
        if (atual == 'X'){
            return 1;
        } else {
            return 2;
        }
    }

    if (tab[0][y] == atual && tab[1][y] == atual && tab[2][y] == atual)
    {
        if (atual == 'X'){
            return 1;
        } else{
            return 2;
        }
    }
    if (tab[1][1] == atual){
        if (tab[0][0] == atual && tab[2][2] == atual){
            if (atual == 'X'){
                return 1;
            } else{
                return 2;
            }
        }
        if (tab[2][0] == atual && tab[0][2] == atual){
            if (atual == 'X'){
                return 1;
            } else{
                return 2;
            }
        }
    }
    
    if (lance == 9){
        return 3;
    } else {
        return 0;
    }
}
#endif
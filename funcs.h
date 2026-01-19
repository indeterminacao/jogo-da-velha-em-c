#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estrutura para armazenar o histórico de cada partida.
 */
typedef struct {
    int resultado;      // 1 ou 2 (Vencedor), 3 (Empate)
    int empates;        // 1 se houve empate, 0 caso contrario
    int jogadas;        // Quantidade total de lances
    char simbolo;       // 'X', 'O' ou '-'
} Partidas;

/**
 * @brief Limpa a tela do terminal.
 * Detecta automaticamente se o sistema é Windows ou Linux/Mac.
 */
void LimpaTerminal();

/**
 * @brief Desenha o tabuleiro 3x3 no terminal.
 * @param tab Matriz do jogo atual.
 */
void estrutura(char (*tab)[3]);

/**
 * @brief Registra a jogada na matriz e atualiza a interface.
 * @param mapa Matriz do jogo.
 * @param simbolo Caractere do jogador atual ('X' ou 'O').
 * @param x Linha escolhida (1-3).
 * @param y Coluna escolhida (1-3).
 */
void renderizacao(char (*mapa)[3], char simbolo, int x, int y);

/**
 * @brief Verifica se a jogada é válida.
 * @return 1: Sucesso | -1: Coordenada inválida | -2: Posição ocupada.
 */
int jogada(char (*mapa)[3], int x, int y);

/**
 * @brief Verifica as condições de vitória ou empate.
 * Utiliza lógica otimizada verificando o centro para as diagonais.
 * @param tab Matriz do jogo.
 * @param x Linha da última jogada.
 * @param y Coluna da última jogada.
 * @param lance Número total de jogadas realizadas.
 * @return 0: Continua | 1: Vitória X | 2: Vitória O | 3: Empate.
 */
int vitoria(char (*tab)[3], int x, int y, int lance);

#endif
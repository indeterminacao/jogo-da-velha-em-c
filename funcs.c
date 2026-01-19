#include "funcs.h"

// Detecta Sistema Operacional para usar o comando correto de limpeza
#ifdef _WIN32
    #define LIMPAR "cls"
#else
    #define LIMPAR "clear"
#endif

//Limpa o terminal
void LimpaTerminal(){
    system(LIMPAR);
}

void estrutura(char (*tab)[3]){
    // Imprime os cabeçalhos das colunas (1, 2, 3)
    printf("     1   2   3\n");
    printf("\n");

    // Loop externo: Percorre as linhas (0 a 2)
    for (int i = 0; i < 3; i++){
        printf(" %d  ", i + 1); // Imprime o índice lateral da linha (1 a 3)

        // Loop interno: Percorre as colunas de cada linha
        for (int j = 0; j < 3; j++){
            printf(" %c ", tab[i][j]); // Imprime o símbolo (X, O ou -) da célula atual

            // Adiciona separador vertical (|) apenas entre as colunas, não após a última
            if (j < 2){
                printf("|"); 
            }
        }
        
        printf("\n"); 

        // Adiciona linha divisória horizontal apenas entre as linhas, não após a última
        if (i < 2){
            printf("    ---+---+---\n"); 
        }
    }
    printf("\n");
}

//Atualiza o estado do jogo e redesenha a interface
void renderizacao(char (*mapa)[3], char simbolo, int x, int y){
    // Atualiza a posição na memória
    // (Subtrai 1 dos índices pois o usuário digita de 1 a 3, mas a matriz vai de 0 a 2)
    mapa[x - 1][y - 1] = simbolo;
    //Da um refresh na tela: apaga tudo que está no terminal e redesenha o tabuleiro atualizado
    LimpaTerminal();
    estrutura(mapa);
}

//Verifica se o lance atual é valido
int jogada(char (*mapa)[3], int x, int y){
    // 1. Validação de Limites:
    // Garante que o usuário não digitou números como 0, 4 ou negativos
    if ((x >= 1 && x <= 3) && (y >= 1 && y <= 3)) {
        
        // 2. Validação de Disponibilidade:
        // Verifica se a célula está vazia ('-').
        // Subtrai 1 de X e Y para converter entrada (1-3) em índice de matriz (0-2).
        if (mapa[x - 1][y - 1] == '-'){
            return 1; // Sucesso: O espaço está livre
        } else {
            return -2; // Falha: Já existe um 'X' ou 'O' aqui
        }
    } else {
        return -1; // Falha: Coordenada inexistente no tabuleiro
    }
}

int vitoria(char (*tab)[3], int x, int y, int lance){
    // Otimização 1: Filtro de Turnos
    // Matematicamente, é impossível ganhar antes do lance 5 (3 do X e 2 do O).
    if (lance < 4){
        return 0;
    } 
    // Ajuste de Índice:
    // Converte a entrada humana (1 a 3) para índices de matriz (0 a 2).
    x--;
    y--;

    char atual = tab[x][y]; // Captura qual símbolo foi jogado (X ou O)

    /* Trava de segurança para não validar vazio */
    if (atual == '-') {
        return 0;
    }

/* * Verificação Direcionada (Linha):
     * Checa apenas a linha 'x' onde a jogada ocorreu.
     * Não perde tempo olhando as outras duas linhas.
     */
    if (tab[x][0] == atual && tab[x][1] == atual && tab[x][2] == atual){
        if (atual == 'X'){
            return 1;
        } else {
            return 2;
        }
    }

/* * Verificação Direcionada (Coluna):
     * Checa apenas a coluna 'y' onde a jogada ocorreu.
     */
    if (tab[0][y] == atual && tab[1][y] == atual && tab[2][y] == atual)
    {
        if (atual == 'X'){
            return 1;
        } else{
            return 2;
        }
    }

/* * Verificação de Diagonais (Otimização Geométrica):
     * Em um tabuleiro 3x3, qualquer vitória diagonal OBRIGATORIAMENTE passa pelo centro [1][1].
     * Se o centro não for igual ao símbolo atual, nem precisamos checar as pontas.
     */
    if (tab[1][1] == atual){
        // Diagonal Principal (Top-Esq -> Inf-Dir)
        if (tab[0][0] == atual && tab[2][2] == atual){
            if (atual == 'X'){
                return 1;
            } else{
                return 2;
            }
        }
        // Diagonal Secundária (Top-Dir -> Inf-Esq)
        if (tab[2][0] == atual && tab[0][2] == atual){
            if (atual == 'X'){
                return 1;
            } else{
                return 2;
            }
        }
    }
    
//É impossivel que uma partida passe de 9 lances
    if (lance == 9){
        return 3;
    } else {
        return 0;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(){
    LimpaTerminal();
    // Ponteiro para o array dinâmico que guardará o histórico
    Partidas *historico = NULL;
    // Variáveis de controle de fluxo e estado do jogo
    int x, y;               // Coordenadas da jogada
    int partidas = 0;       // Contador total de partidas
    int lances = 0;         // Contador de jogadas na partida atual
    int jogo = 1;           // Flag para manter a partida rodando
    int velha = 1;          // Flag para manter o programa rodando (sessão)
    int QuemVai = 1;        // Controla quem começa a partida (1 ou 2)
    char res;               // Armazena o resultado da função vitoria()
    char tab[3][3];         // Matriz do tabuleiro

    // --- TELA INICIAL ---
    printf("### JOGO DA VELHA ###\n");
    printf("Jogador 1 = X | Jogador 2 = O\n");
    printf("A ordem de quem comeca inverte a cada partida.\n\n");
    printf("Pressione Enter para comecar...");

    // Limpeza de buffer para pausar a tela até o Enter
    while(getchar() != '\n') {
    }
    LimpaTerminal();

    // --- LOOP DA SESSÃO (Várias partidas) ---
    while(velha == 1){
        // Reinicia o tabuleiro com '-' (vazio)
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                tab[i][j] = '-';
            }
        }

        jogo = 1;       // Reinicia flag da partida
        lances = 0;     // Zera contador de lances
        int jogador_atual = QuemVai;    // Define quem começa nesta rodada

        // --- LOOP DA PARTIDA (Jogadas) ---
        while(jogo == 1){
            LimpaTerminal();
            estrutura(tab); // Desenha o tabuleiro

            // Define o símbolo visual baseado no número do jogador
            char simbolo_vez;
            if (jogador_atual == 1) {
                simbolo_vez = 'X';
            } else {
                simbolo_vez = 'O';
            }

            printf("Vez do Jogador %d (%c)\n", jogador_atual, simbolo_vez);
            printf("Diga a coordenada (linha coluna): ");
            
            // Leitura da jogada com validação de entrada (evita loop infinito se digitar letras)
            if (scanf("%d %d", &x, &y) != 2) {
                while(getchar() != '\n') { } // Limpa sujeira do buffer
                x = 0; 
                y = 0; // Força erro para cair na validação
            }

            // Verifica se a jogada é válida (retorna 1, -1 ou -2)
            int valida = jogada(tab, x, y);

            if(valida == 1){
                // Jogada válida: Atualiza matriz
                tab[x-1][y-1] = simbolo_vez;
                lances++;
                // Verifica se houve vitória ou empate após a jogada
                res = vitoria(tab, x, y, lances);

                if(res != 0){
                    // Se res != 0, alguém ganhou ou empatou. Encerra o loop.
                    jogo = 0;
                    LimpaTerminal();
                    estrutura(tab); // Mostra tabuleiro final
                } else {
                    // O Jogo continua: Alterna o jogador
                    if (jogador_atual == 1) {
                        jogador_atual = 2;
                    } else {
                        jogador_atual = 1;
                    }
                }
                
            } else if(valida == -1){
                // Tratamento de erro: Coordenada fora do limite
                printf("\n>>> ERRO: COORDENADA INVALIDA! Use 1 a 3. <<<\n");
                printf("Pressione Enter para tentar de novo...");
                while(getchar() != '\n') { } 
                getchar(); 
                
            } else if(valida == -2){
                // Tratamento de erro: Posição ocupada
                printf("\n>>> ERRO: POSICAO JA PREENCHIDA. <<<\n");
                printf("Pressione Enter para tentar de novo...");
                while(getchar() != '\n') { }
                getchar(); 
            }
        } // Fim do Loop da Partida

        // --- FIM DA PARTIDA: REGISTRO E MEMÓRIA ---
        partidas++; 

        // Alocação Dinâmica: Aumenta o array para caber mais uma partida
        Partidas *temporaria = realloc(historico, partidas * sizeof(Partidas));

        if (temporaria == NULL) {
            printf("Erro de memoria!\n");
            free(historico); // Evita memory leak antes de sair
            return 1;
        } else {
            historico = temporaria;
        }

        // Preenche os dados da partida atual na struct
        historico[partidas-1].resultado = res;
        historico[partidas-1].jogadas = lances;
        
        // Define qual símbolo venceu para exibição posterior
        if (res == 1) {
            historico[partidas-1].simbolo = 'X';
        } else if (res == 2) {
            historico[partidas-1].simbolo = 'O';
        } else {
            historico[partidas-1].simbolo = '-';
        }

        // Exibe resultado imediato
        if (res == 3) {
            historico[partidas-1].empates = 1;
            printf("\nDEU VELHA!\n");
        } else {
            historico[partidas-1].empates = 0;
            printf("\nVitoria do Jogador %d (%c)\n", historico[partidas-1].resultado, historico[partidas-1].simbolo);
        }

        // Inverte quem começa a próxima partida (Regra de alternância)
        if (QuemVai == 1) {
            QuemVai = 2;
        } else {
            QuemVai = 1;
        }

        // Pergunta se continua
        printf("\nDeseja jogar novamente? (1-Sim / 0-Nao): ");
        int opcao;
        scanf("%d", &opcao);
        while(getchar() != '\n') {} // Limpa buffer do scanf
        
        if(opcao == 0){
            velha = 0; // Quebra o loop da sessão
        } else {
            LimpaTerminal();
        }
    } // Fim do Loop da Sessão
    
    // --- EXIBIÇÃO DE ESTATÍSTICAS ---
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

    printf("\n\nPressione enter para fechar...");
    // O getchar() pausa a execução.
    // Ao receber um \n (enter), o programa encerra e a janela do terminal se fecha
    // (Isso impede que a janela feche instantaneamente ao executar o .exe diretamente no Windows)
    getchar();

    // Libera toda a memória alocada antes de fechar
    free(historico);
    return 0;
}
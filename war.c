// Jogo de Guerra

// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Constantes globais
#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_MISSOES 2

// Estrutura
typedef struct {
    char nome[MAX_NOME];
    char cor[20];
    int tropas;
} Territorio;

// Setup e memória
Territorio* alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void liberarMemoria(Territorio *mapa);

// Interface
void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa);
void exibirMissao(int missao);

// Lógica
void faseDeAtaque(Territorio *mapa, char jogador[]);
void simularAtaque(Territorio *origem, Territorio *destino);
int sortearMissao();
int verificarVitoria(const Territorio *mapa, int missao, char jogador[]);

// Utilitário
void limparBufferEntrada(); 

// Função Int Main ()

int main() {

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    Territorio *mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro de memória.\n");
        return 1;
    }

    inicializarTerritorios(mapa);

    char jogador[20] = "Azul";
    int missao = sortearMissao();

    int opcao;
    int venceu = 0;

    do {
        exibirMapa(mapa);
        exibirMissao(missao);
        exibirMenuPrincipal();

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                faseDeAtaque(mapa, jogador);
                break;
            case 2:
                venceu = verificarVitoria(mapa, missao, jogador);
                if (venceu)
                    printf("Você venceu!\n");
                else
                    printf("Ainda não venceu.\n");
                break;
        }

        printf("Pressione ENTER...");
        getchar();

    } while(opcao != 0 && !venceu);

    liberarMemoria(mapa);

    return 0;
}
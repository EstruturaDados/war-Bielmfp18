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
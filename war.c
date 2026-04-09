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
typedef struct
{
    char nome[MAX_NOME];
    char cor[20];
    int tropas;
} Territorio;

// Setup e memória
Territorio *alocarMapa();
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

int main()
{

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    Territorio *mapa = alocarMapa();
    if (mapa == NULL)
    {
        printf("Erro de memória.\n");
        return 1;
    }

    inicializarTerritorios(mapa);

    char jogador[20] = "Azul";
    int missao = sortearMissao();

    int opcao;
    int venceu = 0;

    do
    {
        exibirMapa(mapa);
        exibirMissao(missao);
        exibirMenuPrincipal();

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
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

    } while (opcao != 0 && !venceu);

    liberarMemoria(mapa);

    return 0;
}

// Função para alocar memória para o mapa de territórios

Territorio *alocarMapa()
{
    return (Territorio *)calloc(MAX_TERRITORIOS, sizeof(Territorio));
}

void inicializarTerritorios(Territorio *mapa)
{
    char nomes[MAX_TERRITORIOS][MAX_NOME] = {
        "Brasil", "Argentina", "Chile", "Peru", "Uruguai"};
    char cores[2][20] = {"Azul", "Vermelho"};

    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[rand() % 2]);
        mapa[i].tropas = rand() % 5 + 1;
    }
}

void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}

// Interface e funções de exibição

void exibirMenuPrincipal()
{
    printf("\n=== MENU ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

void exibirMapa(const Territorio *mapa)
{
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("%d - %s | %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int missao)
{
    printf("\n=== MISSÃO ===\n");
    if (missao == 0)
        printf("Conquistar 3 territórios\n");
    else
        printf("Eliminar o exército vermelho\n");
}

// Sistema de ataque e lógica de jogo

void faseDeAtaque(Territorio *mapa, char jogador[])
{
    int o, d;

    printf("Origem: ");
    scanf("%d", &o);
    printf("Destino: ");
    scanf("%d", &d);
    limparBufferEntrada();

    if (o >= 0 && o < MAX_TERRITORIOS && d >= 0 && d < MAX_TERRITORIOS)
    {
        if (strcmp(mapa[o].cor, jogador) == 0)
        {
            simularAtaque(&mapa[o], &mapa[d]);
        }
        else
        {
            printf("Território não é seu.\n");
        }
    }
    else
    {
        printf("Índice inválido.\n");
    }
}

void simularAtaque(Territorio *origem, Territorio *destino)
{

    if (origem->tropas < 2)
    {
        printf("Poucas tropas.\n");
        return;
    }

    int atk = rand() % 6 + 1;
    int def = rand() % 6 + 1;

    printf("Atk: %d | Def: %d\n", atk, def);

    if (atk > def)
    {
        destino->tropas--;

        if (destino->tropas <= 0)
        {
            printf("Conquistou!\n");
            strcpy(destino->cor, origem->cor);
            destino->tropas = 1;
            origem->tropas--;
        }
    }
    else
    {
        origem->tropas--;
    }

    int sortearMissao()
    {
        return rand() % MAX_MISSOES;
    }

    int verificarVitoria(const Territorio *mapa, int missao, char jogador[])
    {

        if (missao == 0)
        {
            int count = 0;

            for (int i = 0; i < MAX_TERRITORIOS; i++)
            {
                if (strcmp(mapa[i].cor, jogador) == 0)
                    count++;
            }

            return count >= 3;
        }
        else
        {
            for (int i = 0; i < MAX_TERRITORIOS; i++)
            {
                if (strcmp(mapa[i].cor, "Vermelho") == 0)
                    return 0;
            }
            return 1;
        }
    }

    // Missões e verificação de vitória

    int sortearMissao()
    {
        return rand() % MAX_MISSOES;
    }

    int verificarVitoria(const Territorio *mapa, int missao, char jogador[])
    {

        if (missao == 0)
        {
            int count = 0;

            for (int i = 0; i < MAX_TERRITORIOS; i++)
            {
                if (strcmp(mapa[i].cor, jogador) == 0)
                    count++;
            }

            return count >= 3;
        }
        else
        {
            for (int i = 0; i < MAX_TERRITORIOS; i++)
            {
                if (strcmp(mapa[i].cor, "Vermelho") == 0)
                    return 0;
            }
            return 1;
        }


    }
// Função para limpar o buffer de entrada
    void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
}
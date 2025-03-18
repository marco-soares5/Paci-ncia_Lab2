#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct
{     
    int naipe;
    int valor;
    bool visivel;
    // true = visivel, false = nao visivel
}Carta;

typedef struct
{
    Carta pilha1[13];
    Carta pilha2[13];
    Carta pilha3[13];
    Carta pilha4[13];
    Carta pilha5[13];
    Carta pilha6[13];
    Carta pilha7[13];
    Carta pilhaEspadas[13];
    Carta pilhaPaus[13];
    Carta pilhaCopas[13];
    Carta pilhaOuros[13];
}Jogo;


char lista_de_naipes[4][100] = {"♠", "♣", "♥", "♦"};
//char lista_de_naipes[4][100] = {"♤", "♧", "♡", "♢"};

void mostra_baralho(Carta *baralho)
{
    printf("mostrando o baralho...\n");
    int contador=0;
    for (int i=0; i<4; i++)
    {
        printf("\n");
        for (int j=0; j<13; j++)
        {
            if(baralho[contador].visivel == false)
            {
                printf("[]\t");
            }
            else
            {
                printf("%d%s\t", baralho[contador].valor, lista_de_naipes[baralho[contador].naipe]);
            }
            contador++;
        }
    }
}

void preenche_baralho(Carta *baralho)
{
    int contador=0;

    printf("preenchendo o baralho...\n");
    for (int i=0; i<4; i++)
    {
        for (int j=1; j<=13; j++)
        {
            baralho[contador].naipe = i;
            baralho[contador].valor = j;
            baralho[contador].visivel = false;
            contador++;
        }
    }
    printf("baralho preenchido!\n");
}

void trocar_cartas(Carta *a, Carta *b) //swap
{
    Carta temp;
    temp = *a;
    *a = *b;
    *b = temp;
}   

/*
percorre todas as cartas, trocando elas com outra de um índice aleatório
*/
void embaralhar_baralho(Carta *baralho)
{
    printf("embaralhando o baralho...\n");
    srand(time(NULL));
    for (int i=0; i<52; i++)
    {
        int random = rand()%(52);
        trocar_cartas(&baralho[i], &baralho[random]);
    }
    printf("baralho embaralhado.\n");
}

void cria_pilhas(Carta *baralho, Jogo *jogo)
{
    int contador=0;
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= i; j++){
        }
        contador++;
    }
    printf("\n");
}

void teste_de_baralho(Carta *baralho, Jogo *jogo)
{    
    preenche_baralho(baralho);
    mostra_baralho(baralho);
    printf("\n\n\n");
    embaralhar_baralho(baralho);
    mostra_baralho(baralho);
    printf("\n\n\n");
    cria_pilhas(baralho, jogo);
}

int main()
{
    Carta baralho[52];
    Jogo jogo;
    teste_de_baralho(baralho, jogo)
    return 0;
}
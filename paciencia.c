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
            if(baralho[contador].visivel == true)
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

void cria_pilhas(Carta *baralho)
{
    int contador=0;
    Carta pilha1[13], pilha2[13], pilha3[13], pilha4[13], pilha5[13], pilha6[13], pilha7[13];
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= i; j++){
            switch(i)
            {
            case 1:
                pilha1[j] = baralho[contador];
                break;
            
            case 2:
                pilha2[j] = baralho[contador];
                break;

            case 3:
                pilha3[j] = baralho[contador];
                break;
            
            case 4:
                pilha4[j] = baralho[contador];
                break;
            
            case 5:
                pilha5[j] = baralho[contador];
                break;
                
            case 6:
                pilha6[j] = baralho[contador];
                break;
            
            case 7:
                pilha7[j] = baralho[contador];
                break;

            default:
                break;
            }
            printf("%d%s\t", baralho[contador].valor, lista_de_naipes[baralho[contador].naipe]);
            contador++;
        }
        printf("\n");
    }
}

void teste_de_baralho(Carta *baralho)
{    
    preenche_baralho(baralho);
    mostra_baralho(baralho);
    printf("\n\n\n");
    embaralhar_baralho(baralho);
    mostra_baralho(baralho);
    printf("\n\n\n");
    cria_pilhas(baralho);
}

int main()
{
    Carta baralho[52];
    teste_de_baralho(baralho);
    return 0;
}
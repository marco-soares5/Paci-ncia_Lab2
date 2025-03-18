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
    Carta pilhaEspadas[13];
    Carta pilhaPaus[13];
    Carta pilhaCopas[13];
    Carta pilhaOuros[13];
    bool jogando;
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
            baralho[contador].visivel = true;
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
    Carta pilha1[13], pilha2[13], pilha3[13], pilha4[13], pilha5[13], pilha6[13], pilha7[13];
    int somador = 0;
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= i; j++){
            switch (i)
            {
            case 1:
                pilha1[j].valor = baralho[somador].valor;
                pilha1[j].naipe = baralho[somador].naipe;
                somador++;
            break;
            
            case 2:
                printf("cheguei no 2");
                pilha2[j].valor = baralho[somador].valor;
                pilha2[j].naipe = baralho[somador].naipe;
                somador++;
            break;
            
            case 3:
                pilha3[j].valor = baralho[somador].valor;
                pilha3[j].naipe = baralho[somador].naipe;
                somador++;
            break;

            case 4:
                pilha4[j].valor = baralho[somador].valor;
                pilha4[j].naipe = baralho[somador].naipe;
                somador++;
            break;
            
            case 5:
                pilha5[j].valor = baralho[somador].valor;
                pilha5[j].naipe = baralho[somador].naipe;
                somador++;
            break;
            
            case 6:
                pilha6[j].valor = baralho[somador].valor;
                pilha6[j].naipe = baralho[somador].naipe;
                somador++;
            break;

            case 7:
                pilha7[j].valor = baralho[somador].valor;
                pilha7[j].naipe = baralho[somador].naipe;
                somador++;
            break;
            }
        }
        printf("%d%s\t", pilha1[i].valor, lista_de_naipes[pilha1[i].naipe]);
        printf("\n");
        printf("%d%s\t", pilha2[i].valor, lista_de_naipes[pilha2[i].naipe]);
    }
}

int pede_instrucoes(){
    int instrucao = 1;
    printf("1 - para pegar a carta do topo da pilha 1\n2 - para pegar a carta do topo da pilha 2\n");
    printf("3 - para pegar a carta do topo da pilha 3\n4 - para pegar a carta do topo da pilha 4\n");
    printf("5 - para pegar a carta do topo da pilha 5\n6 - para pegar a carta do topo da pilha 6\n");
    printf("7 - para pegar a carta do topo da pilha 7\n0 - para desistir\n");
    scanf("%d", &instrucao);
    system("cls");
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
    Jogo *jogo;
    teste_de_baralho(baralho);
    
    return 0;
}
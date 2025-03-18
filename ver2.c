#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct{
    int naipe;
    int valor;
    bool visivel; // true = visível, false = não visível
}Carta;

typedef struct{
    Carta pilhaEspadas[13];
    Carta pilhaPaus[13];
    Carta pilhaCopas[13];
    Carta pilhaOuros[13];
    bool jogando;
}Jogo;

char lista_de_naipes[4][100] = {"♠", "♣", "♥", "♦"};

void mostra_baralho(Carta *baralho){
    printf("mostrando o baralho...\n");
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            if(baralho[i].visivel){
                printf("%d%s\t", baralho[i].valor, lista_de_naipes[baralho[i].naipe]);
            }else{
                printf("[]\t");
            }
            if ((i + 1) % 13 == 0){
                printf("\n");
            }
        }
    }
}

void puxa_deposito(Carta *baralho){
    int contador = 0;
    
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            baralho[i].visivel = true;
            break;
        }
        
    }
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            contador++;
            if(contador == 0){
                printf("X");
            }else{
                if(baralho[i].visivel) printf("carta do topo: %d%s ", baralho[i].valor, lista_de_naipes[baralho[i].naipe]);
            }
            
        }
    }
    printf("cartas no baralho: %d\n", contador);
}

void preenche_baralho(Carta *baralho){
    for (int i = 0, contador = 0; i < 4; i++){
        for (int j = 1; j <= 13; j++, contador++){
            baralho[contador].naipe = i;
            baralho[contador].valor = j;
            baralho[contador].visivel = false;
        }
    }
}

void trocar_cartas(Carta *a, Carta *b){
    Carta temp = *a;
    *a = *b;
    *b = temp;
}

void embaralhar_baralho(Carta *baralho){
    srand(time(NULL));
    for (int i = 0; i < 52; i++){
        int random = rand() % 52;
        trocar_cartas(&baralho[i], &baralho[random]);
    }
}

void remover_do_baralho(Carta *baralho, Carta carta_removida) {
    for (int i = 0; i < 52; i++) {
        if (baralho[i].valor == carta_removida.valor && baralho[i].naipe == carta_removida.naipe) {
            baralho[i].valor = 0;
            baralho[i].visivel = false;
            break;
        }
    }
}

void cria_pilhas(Carta *baralho, Carta pilhas[7][13], int *tamanho_pilha){
    int somador = 0;

    for (int i = 0; i < 7; i++){
        for (int j = 0; j <= i; j++){
            pilhas[i][j] = baralho[somador];
            remover_do_baralho(baralho, pilhas[i][j]);
            if(i == j){
                pilhas[i][j].visivel = true;
            }
            somador++;
        }
        tamanho_pilha[i] = i + 1;
    }
}

void mostra_pilhas(Carta pilhas[7][13], int *tamanho_pilha){
    for (int i = 0; i < 7; i++){
        printf("pilha %d: ", i + 1);
        for(int j = 0; j < tamanho_pilha[i]; j++){
            if(j < tamanho_pilha[i] && pilhas[i][j].visivel){
                printf("%d%s ", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
            }else{
                printf("[] ");
            }
        }
        printf("\n");
    }
}

int pede_instrucoes(){
    int instrucao;
    printf("escolha uma pilha para selecionar (1-7) - 0 para sair - 9 para comprar do depósito: ");
    scanf("%d", &instrucao);
    return instrucao;
}

int main(){
    Carta baralho[52];
    Carta pilhas[7][13];
    int tamanho_pilha[7];
    int instrucao;

    preenche_baralho(baralho);
    mostra_baralho(baralho);
    embaralhar_baralho(baralho);
    mostra_baralho(baralho);
    cria_pilhas(baralho, pilhas, tamanho_pilha);
    system("chcp 65001");
    system("cls");

    do{
        printf("paciencia!\n");
    
        mostra_pilhas(pilhas, tamanho_pilha);
        puxa_deposito(baralho);
        instrucao = pede_instrucoes();

        if(instrucao >= 1 && instrucao <= 7){
            printf("\npilha %d selecionada\n", instrucao);
        }else if(instrucao == 0){
            printf("\nsaindo do jogo\n");
        }else{
            printf("\ndigite uma instrucao valida\n");
        }
        system("cls");
    }while (instrucao != 0);

    return 0;
}

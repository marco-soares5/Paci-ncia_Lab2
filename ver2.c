#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_CARTAS 13
#define NUM_PILHAS 7

typedef struct{
    int naipe;
    int valor;
    bool visivel; // true = visível, false = não visível
}Carta;

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
                if(baralho[i].visivel) printf("\nCarta do Topo:     %d%s ", baralho[i].valor, lista_de_naipes[baralho[i].naipe]);
            }
            
        }
    }
    printf("\nCartas no baralho: %d\n", contador);
}

void preenche_baralho(Carta *baralho){
    for (int i = 0, contador = 0; i < 4; i++){
        for (int j = 1; j <= 13; j++, contador++){
            baralho[contador].naipe = i;
            baralho[contador].valor = j;
            baralho[contador].visivel = false;
            // baralho[contador].visivel = true;
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
        printf("Pilha %d: ", i + 1);
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
    printf("\nSelecionar Pilha (1-7) | 9 Comprar do Depósito | 0 Sair: ");
    scanf("%d", &instrucao);
    return instrucao;
}

void executa_instrucao(int instrucao){

    if(instrucao >= 1 && instrucao <= 7){
        printf("\nPilha %d selecionada\n", instrucao);
    }else if(instrucao == 0){
        printf("\nsaindo do jogo\n");
    }else{
        printf("\ndigite uma instrucao valida\n");
    }
}

// supostamente retorna o índice da carta do topo
int carta_topo(int indice_pilha, Carta pilhas[NUM_PILHAS][MAX_CARTAS]){
    int indice_carta;
    
    for (int i=0; i<MAX_CARTAS; i++){
        if (pilhas[indice_pilha][i].valor == 0){
            indice_carta = i-1;
            break;
        }  
    }
    printf("índice da carta do topo da Pilha %d: %d\ncarta do topo da Pilha %d: %d de %s!\n\n", indice_pilha+1, indice_pilha, indice_pilha+1, 
    pilhas[indice_pilha][indice_carta].valor, lista_de_naipes[pilhas[indice_pilha][indice_carta].naipe]);
    
    return indice_carta;
}

// void move_cartas(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int pilhaOrigem, int pilhaDestino){
    
//     pilhas[pilhaOrigem][j];
// }

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

    system("chcp 65001"); //utf-8 para o terminal
    system("cls || clear"); //limpar o terminal windows+linux

    do{
        printf("Paciencia!\n\n");
        int topofica = carta_topo(1, pilhas);
        
        mostra_pilhas(pilhas, tamanho_pilha);
        printf("");
        puxa_deposito(baralho);

        instrucao = pede_instrucoes();
        system("cls || clear");
        executa_instrucao(instrucao);
        
    }while (instrucao != 0);

    return 0;
}

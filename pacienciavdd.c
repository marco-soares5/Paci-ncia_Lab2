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
    printf("Mostrando o baralho...\n");
    for (int i = 0; i < 52; i++){
        if (baralho[i].visivel){
            printf("%d%s\t", baralho[i].valor, lista_de_naipes[baralho[i].naipe]);
        }else{
            printf("[]\t");
        }
        if ((i + 1) % 13 == 0){
            printf("\n");
        }
    }
}

void puxa_deposito(Carta *baralho){
    Carta *primeira_carta = NULL;

    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            baralho[i].visivel = true;
            primeira_carta = &baralho[i];
            break;
        }
    }
    if (primeira_carta != NULL) {
        printf("Carta no primeira_carta: %d de %s\n", primeira_carta->valor, lista_de_naipes[primeira_carta->naipe]);
    } else {
        printf("O deposito está vazio.\n");
    }
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
        printf("Pilha %d: \t", i + 1);
        for(int j = 0; j < tamanho_pilha[i]; j++){
            if(j < tamanho_pilha[i] && pilhas[i][j].visivel){
                printf("%d%s\t", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
            }else{
                printf("?\t");
            }
        }
        printf("\n\n");
    }
}

int pede_instrucoes(){
    int instrucao;
    printf("escolha uma pilha para selecionar (1-7) ou 0 para sair: ");
    scanf("%d", &instrucao);
    return instrucao;
}

// adicionei status de retorno: -1: encerrar jogo, 0: pilha invalida, 1: ok
int instrucao_recebida(int instrucao, Jogo *jogo, int *tamanho_pilha, Carta pilhas[7][13], Carta *baralho){    
    if (instrucao == 0){
        jogo -> jogando = false;
        return -1;
    }
    else if (instrucao >= 1 && instrucao <= 7){
        int index = instrucao-1; //indice da pilha
        if (tamanho_pilha[index]>0){   
            int primeira_carta = tamanho_pilha[index]-1;
            printf("Selecionando a primeira carta da 'Pilha %d':  %d de %s\n", instrucao, pilhas[index][primeira_carta].valor,
            lista_de_naipes[pilhas[index][primeira_carta].naipe]);
            return 1;
        }
    }
    else if (instrucao == 8){
        printf("Puxando deposito...\n");
        puxa_deposito(baralho);
        return 1;
    } 
    else{
        printf("A 'Pilha %d' não é válida!\n", instrucao);
        return 0;
    }
}

void mover_carta(Jogo *jogo, Carta *pilha_antiga, Carta *pilha_nova)
{
    int i=0, ultima_carta;
    
}

int main(){
    Carta baralho[52];
    Carta pilhas[7][13];
    int tamanho_pilha[7];
    int instrucao;
    Jogo jogo;
    jogo.jogando = true;

    preenche_baralho(baralho);
    mostra_baralho(baralho);
    embaralhar_baralho(baralho);
    mostra_baralho(baralho);
    cria_pilhas(baralho, pilhas, tamanho_pilha);    
    system("chcp 65001");
    system("cls||clear");

    do{
        printf("\nPaciencia!\n\n");
    
        mostra_pilhas(pilhas, tamanho_pilha);
        puxa_deposito(baralho);
        instrucao = pede_instrucoes();

        system("cls||clear");
        instrucao_recebida(instrucao, &jogo, tamanho_pilha, pilhas, baralho);

    }while (jogo.jogando == true);



    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_CARTAS 13
#define NUM_PILHAS 7

typedef struct {
    int naipe;
    int valor;
    bool visivel; // true = visível, false = não visível
}Carta;

char lista_de_naipes[4][100] = {"♠", "♣", "♥", "♦"};

void limpa_tela(){
    system("cls || clear");
}

// 30-preto, 31-vermelho, 32-verde, 33-amarelo, 34-azul;
void muda_cor(int cor){
    printf("\033[%dm", cor);
}


void mostra_baralho(Carta *baralho){
    printf("Mostrando o baralho...\n");
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            if(baralho[i].visivel){
                printf("%d%s\t", baralho[i].valor, lista_de_naipes[baralho[i].naipe]);
            }else {
                printf("[]\t");
            }
            if((i + 1) % 13 == 0){
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
            if(baralho[i].visivel) printf("\nCarta do Topo: %d%s", baralho[i].valor, lista_de_naipes[baralho[i].naipe]);
        }
    }
    if(contador == 0){
        printf("\nSem cartas no baralho");
    }
    printf("\nCartas no baralho: %d\n", contador);
}

void preenche_baralho(Carta *baralho){
    for(int i = 0, contador = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++, contador++){
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
    for(int i = 0; i < 52; i++){
        int random = rand() % 52;
        trocar_cartas(&baralho[i], &baralho[random]);
    }
}

void remover_do_baralho(Carta *baralho, Carta carta_removida){
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor == carta_removida.valor && baralho[i].naipe == carta_removida.naipe){
            baralho[i].valor = 0;
            baralho[i].visivel = false;
            break;
        }
    }
}

void cria_pilhas(Carta *baralho, Carta pilhas[7][13], int *tamanho_pilha){
    int somador = 0;

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 13; j++){
            if(j <= i){
                pilhas[i][j] = baralho[somador];
                remover_do_baralho(baralho, pilhas[i][j]);
                if(i == j){
                    pilhas[i][j].visivel = true;
                }
                somador++;
            }else {
                pilhas[i][j].valor = 0;
                pilhas[i][j].naipe = 0;
                pilhas[i][j].visivel = false;
            }
        }
        tamanho_pilha[i] = i + 1;
    }
}

void mostra_pilhas(Carta pilhas[7][13], int *tamanho_pilha){
    for(int i = 0; i < 7; i++){
        printf("\033[0mPilha %d: ", i + 1);
        for(int j = 0; j < tamanho_pilha[i]; j++){
            if(j < tamanho_pilha[i] && pilhas[i][j].visivel){
                if (pilhas[i][j].naipe == 2 || pilhas[i][j].naipe == 3) printf("\033[1;31m%d%s \033[0m", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
                else printf("%d%s ", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
            }else {
                printf("[] ");
            }
        }
        printf("\n");
    }
    printf("\033[0m");
}

int carta_topo(int indice_pilha, Carta pilhas[NUM_PILHAS][MAX_CARTAS]){
    int indice_carta = 0;

    for(int i = 0; i < MAX_CARTAS; i++){
        if(pilhas[indice_pilha][i].valor == 0){
            indice_carta = i - 1;
            break;
        }
    }
    return indice_carta;
}

bool movimento_valido(Carta origem, Carta destino){
    if(origem.naipe <= 1){
        if(destino.naipe > 1){
            if(origem.valor + 1 == destino.valor) return true;
    }
    }else{
        if(destino.naipe <= 1){
            if(origem.valor + 1 == destino.valor) return true;
        }
    }
    return false;
}

void move_cartas(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int *tamanho_pilha, int pilhaOrigem, int pilhaDestino){
    int topo_origem = carta_topo(pilhaOrigem, pilhas);
    int topo_destino = carta_topo(pilhaDestino, pilhas);
    printf("STATUS DA JOGADA: ");
    if(topo_origem < 0){
        muda_cor(33);
        printf("A pilha de origem esta vazia.");
        muda_cor(0);
        printf("\n");
        return;
    }

    Carta carta_origem = pilhas[pilhaOrigem][topo_origem];
    Carta carta_destino = pilhas[pilhaDestino][topo_destino];

    if(topo_destino < 0 || movimento_valido(carta_origem, carta_destino)){

        //só add isso
        if (topo_destino < 0 && pilhas[pilhaOrigem][topo_origem].valor != 13){
            muda_cor(31);
            printf("Só é aceito um Rei!");
            muda_cor(0);
            printf("\n");
            return;
        } 

        pilhas[pilhaDestino][tamanho_pilha[pilhaDestino]] = carta_origem;
        pilhas[pilhaOrigem][topo_origem].valor = 0;
        pilhas[pilhaOrigem][topo_origem].visivel = false;

        tamanho_pilha[pilhaDestino]++;
        tamanho_pilha[pilhaOrigem]--;

        if(tamanho_pilha[pilhaOrigem] > 0){
            pilhas[pilhaOrigem][tamanho_pilha[pilhaOrigem] - 1].visivel = true;
        }
        muda_cor(32);
        printf("Carta %d %s movida para a pilha %d", carta_origem.valor, lista_de_naipes[carta_origem.naipe], pilhaDestino + 1);
        muda_cor(0);
        printf("\n\n");
    }else {
        muda_cor(31);
        printf("Movimento invalido!");
        muda_cor(0);
        printf("\n\n");
    }
}

void compra_carta(Carta *baralho, Carta descarte[52]){
    for(int i = 0; i < 52; i++){
        descarte[i].visivel = true; // iniciar o descarte como invisivel
    }
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            descarte[i].valor = baralho[i].valor;
            descarte[i].naipe = baralho[i].naipe;
            remover_do_baralho(baralho, baralho[i]);
            break;
        }
    }
}

int pede_instrucoes(){
    int instrucao;
    do{
        printf("\n(1-7) - Selecionar pilha | 8 - Comprar do Deposito | 0 - Sair: ");
        scanf("%d", &instrucao);
        printf("\n");

        if(instrucao >= 1 && instrucao <= 7){
            muda_cor(33);
            printf("Pilha %d selecionada", instrucao);
            muda_cor(0);
            printf("\n\n");
        }else if(instrucao == 8){
            muda_cor(33);
            printf("Carta comprada");
            muda_cor(0);
            printf("\n\n");
        }else if(instrucao != 0){
            muda_cor(31);
            printf("Digite uma instrução valida");
            muda_cor(0);
            printf("\n\n");
        }
    }while(!(instrucao >= 0 && instrucao <= 8));

    return instrucao;
}

int main(){
    Carta baralho[52];
    Carta pilhas[7][13];
    Carta pilha_descarte[52];
    int tamanho_pilha[7];
    int instrucao;

    preenche_baralho(baralho);
    embaralhar_baralho(baralho);
    cria_pilhas(baralho, pilhas, tamanho_pilha);

    system("chcp 65001"); // utf8 para o terminal
    limpa_tela();

    printf("VAMOS JOGAR PACIENCIA - aperte ENTER pra começar: ");
    getchar();
    limpa_tela();

    do{
        printf("Paciencia!\n\n");
        
        mostra_pilhas(pilhas, tamanho_pilha);
        puxa_deposito(baralho);
        instrucao = pede_instrucoes();
    
        if(instrucao == 8){
            compra_carta(baralho, pilha_descarte);
        }else
        if(instrucao >= 1 && instrucao <= 7){
            int pilhaOrigem = instrucao - 1;
            int pilhaDestino;
    
            printf("Escolha a pilha de destino(1-7): ");
            scanf("%d", &pilhaDestino);
            pilhaDestino--;
            limpa_tela();
            move_cartas(pilhas, tamanho_pilha, pilhaOrigem, pilhaDestino);
        }
    }while(instrucao != 0);

    return 0;
}
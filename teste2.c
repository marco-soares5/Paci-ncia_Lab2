
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

void conta_cartas_baralho(Carta *baralho){
    int contador = 0;

    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            contador++;
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
            baralho[i].naipe = 0;
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
            if(pilhas[i][j].valor != 0){
                if(j < tamanho_pilha[i] && pilhas[i][j].visivel){
                    if (pilhas[i][j].naipe == 2 || pilhas[i][j].naipe == 3) printf("\033[1;31m%d%s \033[0m", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
                    else printf("%d%s ", pilhas[i][j].valor, lista_de_naipes[pilhas[i][j].naipe]);
                }else {
                    printf("[] ");
                }
            }
        }
        printf("\n");
    }

    // printf("\033[0m");
    // for (int i=0; i<4; i++){
    //     printf("Pilha Final %d: \t");
    //     for (int j=0; j<MAX_CARTAS; j++){
    //         printf("%d ", );
    //     }
    // }
    // printf("\n\n");
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

        if(tamanho_pilha[pilhaOrigem] > 0) pilhas[pilhaOrigem][tamanho_pilha[pilhaOrigem] - 1].visivel = true;
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

void compra_carta(Carta *baralho, Carta descarte[52], int *primeira_carta){
    // isso aqui tava reiniicando o descarte aqui eu acho, to passando como argumento uma variável declarada na main, pq daí eu passo pra função de mostrar o depósito também
    // agora essa função percorre todo o baralho até encontrar um valor diferente de 0, ai tu manda isso pra primeira carta q vai ser o índice da primeira carta que está no descar
    // q daí tu atualiza cada vez que tu roda essa função
    for(int i = 0; i < 52; i++){
        if(baralho[i].valor != 0){
            (*primeira_carta)++; // um amigo me explicou, não entendi pq tem q estar entre parentesesy
            descarte[*primeira_carta] = baralho[i];
            descarte[*primeira_carta].visivel = true;
            remover_do_baralho(baralho, baralho[i]);
            break;
        }
    }
}

int pede_instrucoes(){
    int instrucao;
    do{
        printf("\n(1-7) - Selecionar pilha | 8 - Comprar do deposito | 9 - Mover carta do deposito | 0 - Sair: ");
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
        }
        else if(instrucao == 9){
            muda_cor(33);
            printf("Pilha de descarte selecionada");
            muda_cor(0);
            printf("\n\n");
        }else if(instrucao != 0){
            muda_cor(31);
            printf("Digite uma instrução valida");
            muda_cor(0);
            printf("\n\n");
        }
    }while(!(instrucao >= 0 && instrucao <= 9));
    return instrucao;
}

// pilhas globais
Carta pilhaEspadas[MAX_CARTAS]; 
Carta pilhaPaus[MAX_CARTAS]; 
Carta pilhaOuros[MAX_CARTAS];
Carta pilhaCopas[MAX_CARTAS];

void inicializar_globais(Carta pilha[MAX_CARTAS]){
    for (int i=0; i<MAX_CARTAS; i++){
        pilha[i].valor = 0;
        pilha[i].naipe = 0;
        pilha[i].visivel = false;
    }
}

void inicializar_pilhas_globais(){
    inicializar_globais(pilhaCopas);
    inicializar_globais(pilhaOuros);
    inicializar_globais(pilhaPaus);
    inicializar_globais(pilhaEspadas);
}


void pilhas_finais(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int pilhaOrigem, int *tamanho_pilha) {
    int topo_origem = carta_topo(pilhaOrigem, pilhas);
    if (topo_origem < 0) {
        muda_cor(31);
        printf("A pilha de origem está vazia.\n");
        muda_cor(0);
        return;
    }

    Carta carta_origem = pilhas[pilhaOrigem][topo_origem];
    Carta *pilha_final;

    // Seleciona a pilha final correspondente ao naipe da carta
    switch (carta_origem.naipe) {
        case 0:
            pilha_final = pilhaEspadas;
            break;
        case 1:
            pilha_final = pilhaPaus;
            break;
        case 2:
            pilha_final = pilhaOuros;
            break;
        case 3:
            pilha_final = pilhaCopas;
            break;
        default:
            muda_cor(31);
            printf("Naipe inválido.\n");
            muda_cor(0);
            return;
    }

    // Verifica o valor esperado da próxima carta na pilha final
    int proximo_valor = 1; // O primeiro valor aceito é 1
    for (int i = 0; i < MAX_CARTAS; i++) {
        if (pilha_final[i].valor != 0) {
            proximo_valor = pilha_final[i].valor + 1;
        } else {
            break;
        }
    }

    if (carta_origem.valor == proximo_valor) {
        // Adiciona a carta na pilha final
        for (int i = 0; i < MAX_CARTAS; i++) {
            if (pilha_final[i].valor == 0) {
                pilha_final[i] = carta_origem;
                break;
            }
        }

        // Remove a carta da pilha de origem
        pilhas[pilhaOrigem][topo_origem].valor = 0;
        pilhas[pilhaOrigem][topo_origem].naipe = 0;
        pilhas[pilhaOrigem][topo_origem].visivel = false;
        tamanho_pilha[pilhaOrigem]--;

        // Torna a próxima carta visível, se houver
        if (tamanho_pilha[pilhaOrigem] > 0) {
            pilhas[pilhaOrigem][tamanho_pilha[pilhaOrigem] - 1].visivel = true;
        }

        muda_cor(32);
        printf("Carta %d%s movida para a pilha final do naipe %s.\n", 
               carta_origem.valor, lista_de_naipes[carta_origem.naipe], lista_de_naipes[carta_origem.naipe]);
        muda_cor(0);
    } else {
        muda_cor(31);
        printf("Movimento inválido! O valor da carta deve ser %d.\n", proximo_valor);
        muda_cor(0);
    }
}

void mostrar_deposito(Carta pilha_descarte[], int deposito_posição) {
    printf("A carta no deposito é: ");
    if (deposito_posição > 0 && pilha_descarte[deposito_posição].valor != 0) {
        Carta carta = pilha_descarte[deposito_posição];

        if (carta.naipe == 2 || carta.naipe == 3) muda_cor(31); 
        else muda_cor(0); 
        
        printf("[%d%s]", carta.valor, lista_de_naipes[carta.naipe]);
        muda_cor(0); 
    } else {
        printf("[ ]");
    }
}

void move_carta_deposito(Carta pilhas[NUM_PILHAS][MAX_CARTAS], int *tamanho_pilha, int deposito_posição, int pilhaDestino, Carta pilha_deposito[]) {
    int topo_destino = carta_topo(pilhaDestino, pilhas);

    if(deposito_posição <= 0){
        printf("A pilha de origem esta vazia");
        return;
    }
    
    Carta carta_deposito = pilha_deposito[deposito_posição];
    Carta carta_destino = pilhas[pilhaDestino][topo_destino];

    if (topo_destino < 0 && carta_deposito.valor ==13 || movimento_valido(carta_deposito, carta_destino)){
        if(carta_deposito.valor != 13 && topo_destino < 0){
            printf("Só é aceito um rei aqui");
        }
        if (carta_deposito.valor == 13){
            muda_cor(31);
            pilhas[pilhaDestino][0] = carta_deposito;
            pilha_deposito[deposito_posição].valor = 0;
            tamanho_pilha[pilhaDestino]++;

            printf("Carta %d%s movida do depósito para a pilha %d", carta_deposito.valor, lista_de_naipes[carta_deposito.naipe], pilhaDestino);
        } else {
        pilhas[pilhaDestino][tamanho_pilha[pilhaDestino]] = carta_deposito; // acessa o tamanho de pilhadestino, pega o indice e joga a carta deposito
        pilha_deposito[deposito_posição].valor = 0; // remove da pilha de origem

        tamanho_pilha[deposito_posição]--;
        tamanho_pilha[pilhaDestino]++;
        printf("Carta %d%s movida do depósito para a pilha %d", carta_deposito.valor, lista_de_naipes[carta_deposito.naipe], pilhaDestino + 1);
        } 
    } else{
        printf("Movimento inválido");
    } 
}    

int main(){
    Carta baralho[52];
    Carta pilhas[7][13];
    Carta pilha_descarte[52]; // sobram 24 depois que as cartas são distribuidas pra as pilhas
    int tamanho_pilha[7];
    int instrucao;
    int primeira_carta = 0;
    int deposito_posição = 0;

    preenche_baralho(baralho);
    embaralhar_baralho(baralho);
    cria_pilhas(baralho, pilhas, tamanho_pilha);

    system("chcp 65001"); // utf8 para o terminal
    limpa_tela();

    printf("VAMOS JOGAR PACIENCIA - aperte ENTER pra começar: ");
    inicializar_pilhas_globais();
    getchar();
    limpa_tela();

    do{
        printf("Paciencia!\n\n");
        
        mostra_pilhas(pilhas, tamanho_pilha);
        mostrar_deposito(pilha_descarte, deposito_posição);
        conta_cartas_baralho(baralho);
        instrucao = pede_instrucoes();
    
        // virar uma carta do baralho
        if(instrucao == 8){ 
            compra_carta(baralho, pilha_descarte, &primeira_carta);
            limpa_tela();
            deposito_posição++;
        }
        // selecionar carta do topo da pilha
        else if(instrucao >= 1 && instrucao <= 7){
            int pilhaOrigem = instrucao - 1;
            int pilhaDestino;
    
            printf("Escolha a pilha de destino (1-7) ou 8 para adicionar na pilha final do naipe: ");
            scanf("%d", &pilhaDestino);
            pilhaDestino--;
            limpa_tela();

            if(pilhaDestino >= 0 && pilhaDestino <= 6) move_cartas(pilhas, tamanho_pilha, pilhaOrigem, pilhaDestino);
            else if(pilhaDestino == 7) pilhas_finais(pilhas, pilhaOrigem, tamanho_pilha);
        } else if(instrucao == 9){
            int pilhaDestino;
            printf("Escolha a pilha de destino (1-7) ou 8 para adicionar na pilha final do naipe: ");
            scanf("%d", &pilhaDestino);
            pilhaDestino--;
            limpa_tela();

            if (pilhaDestino >= 0 && pilhaDestino <= 6){
                move_carta_deposito(pilhas, tamanho_pilha, deposito_posição, pilhaDestino, pilha_descarte);}
                else {
                    muda_cor(31);
                    printf("Movimento invalido!");
                    muda_cor(0);
                    printf("\n\n");
                }
            }
    }while(instrucao != 0);

    return 0;
}

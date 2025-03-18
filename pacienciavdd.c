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
    printf("escolha uma pilha para selecionar (1-7) ou 0 para sair: ");
    scanf("%d", &instrucao);
    return instrucao;
}

void instrução_recebida1(int instrução, Jogo *jogo, int *tamanho_pilha, Carta pilhas[7][13], Carta *baralho){
    switch (instrução)
    {
    case 0:
        jogo -> jogando = false;
        printf("Botão 0 digitado, saindo do jogo!1");
        break;
    case 1:
        if (tamanho_pilha[0] > 0){
            int primeira_carta = tamanho_pilha[0] - 1;
            printf("Selecionando a priemeira carta da pilha 1");   
            lista_de_naipes[pilhas[0][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 2:
        if (tamanho_pilha[1] > 0){
            int primeira_carta = tamanho_pilha[1] - 1;
            printf("Selecionando a segunda carta da pilha 2");   
            lista_de_naipes[pilhas[1][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 3:
        if (tamanho_pilha[2] > 0){
            int primeira_carta = tamanho_pilha[2] - 1;
            printf("Selecionando a priemeira carta da pilha 3");   
            lista_de_naipes[pilhas[2][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 4:
        if (tamanho_pilha[3] > 0){
            int primeira_carta = tamanho_pilha[3] - 1;
            printf("Selecionando a priemeira carta da pilha 4");   
            lista_de_naipes[pilhas[3][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 5:
        if (tamanho_pilha[4] > 0){
            int primeira_carta = tamanho_pilha[4] - 1;
            printf("Selecionando a priemeira carta da pilha 5");   
            lista_de_naipes[pilhas[4][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 6:
        if (tamanho_pilha[5] > 0){
            int primeira_carta = tamanho_pilha[5] - 1;
            printf("Selecionando a priemeira carta da pilha 6");   
            lista_de_naipes[pilhas[5][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 7:
        if (tamanho_pilha[6] > 0){
            int primeira_carta = tamanho_pilha[6] - 1;
            printf("Selecionando a priemeira carta da pilha 7");   
            lista_de_naipes[pilhas[6][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 8: //pegar uma carta e jogar na pilha de descarte
        puxa_deposito(baralho);
    }
}

void instrução_destino(int instrução, Jogo *jogo, int *tamanho_pilha, Carta pilhas[7][13]){
    switch (instrução)
    {
    case 0:
        jogo -> jogando = false;
        printf("Botão 0 digitado, saindo do jogo!1");
        break;
    case 1:
        if (tamanho_pilha[0] == 0){
            int primeira_carta = tamanho_pilha[0] - 1;
            printf("Selecionando a priemeira carta da pilha 1");   
            lista_de_naipes[pilhas[0][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 2:
        if (tamanho_pilha[1] == 0){
            int primeira_carta = tamanho_pilha[1] - 1;
            printf("Selecionando a segunda carta da pilha 2");   
            lista_de_naipes[pilhas[1][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 3:
        if (tamanho_pilha[2] == 0){
            int primeira_carta = tamanho_pilha[2] - 1;
            printf("Selecionando a priemeira carta da pilha 3");   
            lista_de_naipes[pilhas[2][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 4:
        if (tamanho_pilha[3] == 0){
            int primeira_carta = tamanho_pilha[3] - 1;
            printf("Selecionando a priemeira carta da pilha 4");   
            lista_de_naipes[pilhas[3][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 5:
        if (tamanho_pilha[4] == 0){
            int primeira_carta = tamanho_pilha[4] - 1;
            printf("Selecionando a priemeira carta da pilha 1");   
            lista_de_naipes[pilhas[4][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 6:
        if (tamanho_pilha[5] == 0){
            int primeira_carta = tamanho_pilha[5] - 1;
            printf("Selecionando a priemeira carta da pilha 1");   
            lista_de_naipes[pilhas[5][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    case 7:
        if (tamanho_pilha[6] == 0){
            int primeira_carta = tamanho_pilha[6] - 1;
            printf("Selecionando a priemeira carta da pilha 1");   
            lista_de_naipes[pilhas[6][primeira_carta].naipe];
        } else {printf("A pilha está vazia");}
        break;
    }
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
    system("cls");

    do{
        printf("paciencia!\n");
    
        mostra_pilhas(pilhas, tamanho_pilha);
        puxa_deposito(baralho);
        instrucao = pede_instrucoes();

        instrução_recebida1(instrucao, &jogo, tamanho_pilha, pilhas, baralho);

        system("cls");
    }while (jogo.jogando = true);

    return 0;
}
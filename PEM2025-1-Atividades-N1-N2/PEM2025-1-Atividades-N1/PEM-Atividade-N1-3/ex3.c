/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Gerenciar estoque em armazém tridimensional *
* Data - 21/03/2025                                      * 
* Autor: KAUÊ RAFAEL MAZZONE DA SILVA                    *
*--------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_RUAS 3
#define NUM_POSICOES 10
#define MAX_COD 20

// Converte uma letra de rua ('A', 'B' ou 'C') para o índice correspondente (0, 1 ou 2)
int ruaParaIndice(char rua) {
    switch (toupper(rua)) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        default:  return -1;
    }
}

// Retorna a letra da rua a partir do índice
char indiceParaRua(int i) {
    if (i == 0) return 'A';
    if (i == 1) return 'B';
    if (i == 2) return 'C';
    return '?';
}

// Busca um produto no estoque.
// Se encontrado, atualiza os parâmetros ruaEncontrada e posEncontrada e retorna 1.
// Caso contrário, retorna 0.
int buscarProduto(char estoque[NUM_RUAS][NUM_POSICOES][MAX_COD],
                  const char *codigo,
                  int *ruaEncontrada,
                  int *posEncontrada) {
    for (int r = 0; r < NUM_RUAS; r++) {
        for (int p = 0; p < NUM_POSICOES; p++) {
            if (strcmp(estoque[r][p], codigo) == 0) {
                *ruaEncontrada = r;
                *posEncontrada = p;
                return 1;
            }
        }
    }
    return 0;
}

// Inicializa o estoque com strings vazias
void inicializarEstoque(char estoque[NUM_RUAS][NUM_POSICOES][MAX_COD]) {
    for (int r = 0; r < NUM_RUAS; r++) {
        for (int p = 0; p < NUM_POSICOES; p++) {
            estoque[r][p][0] = '\0';
        }
    }
}

// Exibe o menu principal
void exibirMenu() {
    printf("\n========================================\n");
    printf("         GESTAO DE ESTOQUE (3D)         \n");
    printf("========================================\n");
    printf("1 - Estocar Produto\n");
    printf("2 - Retirar Produto\n");
    printf("3 - Mostrar Estoque\n");
    printf("4 - Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para estocar um produto no estoque
void estocarProduto(char estoque[NUM_RUAS][NUM_POSICOES][MAX_COD]) {
    char codigo[MAX_COD];
    printf("\nDigite o codigo do produto (ex: S123): ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    int ruaE, posE;
    if (buscarProduto(estoque, codigo, &ruaE, &posE)) {
        printf("O produto %s ja esta armazenado na Rua %c, Posicao %d.\n",
               codigo, indiceParaRua(ruaE), posE + 1);
    } else {
        printf("Produto %s nao encontrado. Informe onde deseja estocar.\n", codigo);
        char ruaChar;
        int posicao;
        printf("Digite a Rua (A, B ou C): ");
        scanf(" %c", &ruaChar);
        printf("Digite a Posicao (1..10): ");
        scanf("%d", &posicao);
        getchar(); // consome o '\n' pendente

        int indiceRua = ruaParaIndice(ruaChar);
        int indicePos = posicao - 1;
        if (indiceRua < 0 || indiceRua >= NUM_RUAS || indicePos < 0 || indicePos >= NUM_POSICOES) {
            printf("Entrada de rua/posicao invalida.\n");
        } else {
            if (estoque[indiceRua][indicePos][0] == '\0') {
                strcpy(estoque[indiceRua][indicePos], codigo);
                printf("Produto %s estocado em Rua %c, Posicao %d.\n",
                       codigo, toupper(ruaChar), posicao);
            } else {
                printf("A posicao Rua %c, Posicao %d ja esta ocupada pelo produto %s.\n",
                       toupper(ruaChar), posicao, estoque[indiceRua][indicePos]);
            }
        }
    }
}

// Função para retirar um produto do estoque
void retirarProduto(char estoque[NUM_RUAS][NUM_POSICOES][MAX_COD]) {
    char codigo[MAX_COD];
    printf("\nDigite o codigo do produto a retirar: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    int ruaE, posE;
    if (buscarProduto(estoque, codigo, &ruaE, &posE)) {
        estoque[ruaE][posE][0] = '\0';
        printf("Produto %s foi retirado do estoque (Rua %c, Posicao %d).\n",
               codigo, indiceParaRua(ruaE), posE + 1);
    } else {
        printf("Produto %s nao encontrado no estoque.\n", codigo);
    }
}

// Função para exibir o estoque atual
void mostrarEstoque(char estoque[NUM_RUAS][NUM_POSICOES][MAX_COD]) {
    printf("\n--- ESTOQUE ATUAL ---\n");
    for (int r = 0; r < NUM_RUAS; r++) {
        for (int p = 0; p < NUM_POSICOES; p++) {
            if (estoque[r][p][0] != '\0') {
                printf("Rua %c, Posicao %d -> %s\n",
                       indiceParaRua(r), p + 1, estoque[r][p]);
            }
        }
    }
    printf("----------------------\n");
}

int main() {
    char estoque[NUM_RUAS][NUM_POSICOES][MAX_COD];
    inicializarEstoque(estoque);

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // consome o '\n' pendente

        switch (opcao) {
            case 1:
                estocarProduto(estoque);
                break;
            case 2:
                retirarProduto(estoque);
                break;
            case 3:
                mostrarEstoque(estoque);
                break;
            case 4:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}

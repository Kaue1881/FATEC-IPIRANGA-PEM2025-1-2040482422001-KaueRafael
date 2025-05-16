#include <stdio.h>

// Função que ordena o vetor usando Insertion Sort com ponteiros
void insertionSort(int* vetor, int n) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = *(vetor + i);  // pega o valor atual
        j = i - 1;

        // move elementos maiores para frente
        while (j >= 0 && *(vetor + j) > chave) {
            *(vetor + j + 1) = *(vetor + j);
            j--;
        }

        // insere a chave no lugar certo
        *(vetor + j + 1) = chave;
    }
}

int main() {
    int n;

    printf("Insira o total de numeros: ");
    scanf("%d", &n);

    int armazenador[n];  // vetor com tamanho definido pelo usuário

    // Leitura dos valores
    for (int i = 0; i < n; i++) {
        printf("armazenador[%d]: ", i);
        scanf("%d", &armazenador[i]);
    }

    // Chama a função de ordenação
    insertionSort(armazenador, n);

    // Exibe vetor ordenado
    printf("\nVetor ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("armazenador[%d] = %d\n", i, armazenador[i]);
    }

    return 0;
}

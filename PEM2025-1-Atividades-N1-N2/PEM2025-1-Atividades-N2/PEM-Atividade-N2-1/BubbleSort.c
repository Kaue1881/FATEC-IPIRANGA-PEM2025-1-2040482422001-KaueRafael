#include <stdio.h>
void comparacaoAdjacente(int* vetor, int n) {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            // usando tecnica de ponteiros para acessar os valores
            if (*(vetor + j) > *(vetor + j + 1)) {
                printf("Trocando %d por %d\n", *(vetor + j), *(vetor + j + 1));
                temp = *(vetor + j);
                *(vetor + j) = *(vetor + j + 1);
                *(vetor + j + 1) = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Insira o total de numeros: ");
    scanf("%d", &n);
    
    int armazenador[n];
    
    for (int i = 0; i < n; i++) {
        printf("armazenador[%d]: ", i);
        scanf("%d", &armazenador[i]);
    }

    // passa o endereço do primeiro elemento (ou só o nome do vetor)
    comparacaoAdjacente(armazenador, n);

    printf("\nVetor ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("armazenador[%d] = %d\n", i, armazenador[i]);
    }

    return 0;
}

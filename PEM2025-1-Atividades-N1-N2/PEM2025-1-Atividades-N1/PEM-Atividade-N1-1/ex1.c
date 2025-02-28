/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Aula 1-Variaveis-comp-homo       *
* Data - 29/02/2025                                      * 
* Autor:KAUE RAFAEL MAZZONE DA SILVA                     *
*--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 100

// Estrutura para armazenar informações de um candidato
typedef struct {
    char nome[100];
    float prova_objetiva;
    float prova_pratica;
    float analise_curricular;
    float nota_adicional;
    float nota_final;
} Candidato;

// Função para calcular a nota final de um candidato
float calcularNotaFinal(float objetiva, float pratica, float curricular, float adicional) {
    return (objetiva * 0.5) + (pratica * 0.2) + (curricular * 0.1) + (adicional * 0.2);
}

// Função para ordenar os candidatos por nota final (bubble sort para simplicidade)
void ordenarCandidatos(Candidato candidatos[], int n) {
    int i, j;
    Candidato temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (candidatos[j].nota_final < candidatos[j + 1].nota_final) {
                temp = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    Candidato candidatos[MAX_CANDIDATOS];

    printf("Quantos candidatos deseja cadastrar? (Máx %d): ", MAX_CANDIDATOS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_CANDIDATOS) {
        printf("Número inválido de candidatos.\n");
        return 1;
    }
    getchar(); // Consumir o caractere de nova linha deixado pelo scanf

    for (i = 0; i < n; i++) {
        printf("\nCandidato %d\n", i + 1);
        printf("Nome: ");
        if (fgets(candidatos[i].nome, sizeof(candidatos[i].nome), stdin) == NULL) {
            printf("Erro na leitura do nome.\n");
            return 1;
        }
        // Remover o caractere de nova linha, se presente
        size_t len = strlen(candidatos[i].nome);
        if (len > 0 && candidatos[i].nome[len - 1] == '\n') {
            candidatos[i].nome[len - 1] = '\0';
        }

        printf("Nota da prova objetiva (0-100): ");
        if (scanf("%f", &candidatos[i].prova_objetiva) != 1 || candidatos[i].prova_objetiva < 0 || candidatos[i].prova_objetiva > 100) {
            printf("Nota inválida.\n");
            return 1;
        }

        printf("Nota da prova prática (0-100): ");
        if (scanf("%f", &candidatos[i].prova_pratica) != 1 || candidatos[i].prova_pratica < 0 || candidatos[i].prova_pratica > 100) {
            printf("Nota inválida.\n");
            return 1;
        }

        printf("Nota da análise curricular (0-100): ");
        if (scanf("%f", &candidatos[i].analise_curricular) != 1 || candidatos[i].analise_curricular < 0 || candidatos[i].analise_curricular > 100) {
            printf("Nota inválida.\n");
            return 1;
        }

        printf("Nota adicional (0-100): ");
        if (scanf("%f", &candidatos[i].nota_adicional) != 1 || candidatos[i].nota_adicional < 0 || candidatos[i].nota_adicional > 100) {
            printf("Nota inválida.\n");
            return 1;
        }

        candidatos[i].nota_final = calcularNotaFinal(
            candidatos[i].prova_objetiva,
            candidatos[i].prova_pratica,
            candidatos[i].analise_curricular,
            candidatos[i].nota_adicional
        );

        getchar(); // Consumir o caractere de nova linha deixado pelo scanf
    }

    ordenarCandidatos(candidatos, n);

    printf("\nClassificação dos candidatos:\n");
    for (i = 0; i < n; i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].nota_final);
    }

    return 0;
}

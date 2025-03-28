#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

// Função recursiva para listar diretórios e arquivos com indentação e exibição do nível
void listar_diretorios(const char *caminho, int nivel) {
    DIR *dir;
    struct dirent *entrada;

    // Tenta abrir o diretório fornecido
    if (!(dir = opendir(caminho))) {
        for (int i = 0; i < nivel; i++) {
            printf("    ");
        }
        printf("Nao foi possivel abrir: %s\n", caminho);
        return;
    }

    // Percorre cada entrada no diretório
    while ((entrada = readdir(dir)) != NULL) {
        // Ignora as entradas especiais "." e ".."
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
            continue;

        // Monta o caminho completo para o item atual
        char caminho_completo[1024];
        snprintf(caminho_completo, sizeof(caminho_completo), "%s/%s", caminho, entrada->d_name);

        // Imprime a indentação proporcional ao nível de profundidade
        for (int i = 0; i < nivel; i++) {
            printf("    ");
        }
        
        // Exibe o nível atual junto com o nome
        printf("[Nivel %d] ", nivel);

        // Verifica se o item é um diretório ou arquivo
        struct stat info;
        if (stat(caminho_completo, &info) == -1) {
            perror("Erro ao acessar informações do arquivo");
            continue;
        }

        // Se for diretório, imprime com a tag [DIR] e chama recursivamente
        if (S_ISDIR(info.st_mode)) {
            printf("[DIR] %s\n", entrada->d_name);
            listar_diretorios(caminho_completo, nivel + 1);
        } else {
            // Se for arquivo, apenas imprime seu nome
            printf("%s\n", entrada->d_name);
        }
    }
    closedir(dir);
}

int main() {
    char caminho[1024];

    printf("Digite o caminho do diretorio: ");
    scanf("%1023s", caminho);

    // Inicia a listagem a partir do caminho informado, no nível 0
    listar_diretorios(caminho, 0);

    return 0;
}

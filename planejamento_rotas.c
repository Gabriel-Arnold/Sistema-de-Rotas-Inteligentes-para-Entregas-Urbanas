#include <stdio.h>

#define MAX_VERTICES 50

typedef struct {
    int vertices;
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

void inicializarGrafo(Grafo *grafo, int vertices) {
    int i, j;

    grafo->vertices = vertices;

    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            grafo->matriz[i][j] = 0;
        }
    }
}

void inserirAresta(Grafo *grafo, int origem, int destino, int peso) {
    if (origem < 0 || origem >= grafo->vertices || destino < 0 || destino >= grafo->vertices) {
        printf("Vertices invalidos.\n");
        return;
    }

    if (peso <= 0) {
        printf("O peso deve ser maior que zero.\n");
        return;
    }

    grafo->matriz[origem][destino] = peso;
    grafo->matriz[destino][origem] = peso;
}

void carregarExemplo(Grafo *grafo) {
    inicializarGrafo(grafo, 6);

    inserirAresta(grafo, 0, 1, 4);
    inserirAresta(grafo, 0, 2, 2);
    inserirAresta(grafo, 1, 2, 1);
    inserirAresta(grafo, 1, 3, 5);
    inserirAresta(grafo, 2, 3, 8);
    inserirAresta(grafo, 2, 4, 10);
    inserirAresta(grafo, 3, 4, 2);
    inserirAresta(grafo, 3, 5, 6);
    inserirAresta(grafo, 4, 5, 3);
}

void exibirMatriz(Grafo *grafo) {
    int i, j;

    printf("\nMatriz de adjacencia (0 indica ausencia de rua):\n\n");
    printf("    ");

    for (i = 0; i < grafo->vertices; i++) {
        printf("%4c", 'A' + i);
    }

    printf("\n");

    for (i = 0; i < grafo->vertices; i++) {
        printf("%4c", 'A' + i);

        for (j = 0; j < grafo->vertices; j++) {
            printf("%4d", grafo->matriz[i][j]);
        }

        printf("\n");
    }
}

int lerVertice(char mensagem[], int quantidadeVertices) {
    char letra;

    printf("%s (A-%c): ", mensagem, 'A' + quantidadeVertices - 1);
    scanf(" %c", &letra);

    if (letra >= 'a' && letra <= 'z') {
        letra = letra - 32;
    }

    return letra - 'A';
}

void cadastrarGrafo(Grafo *grafo) {
    int vertices, arestas, i;
    int origem, destino, peso;

    do {
        printf("Digite o numero de vertices (minimo 6, maximo %d): ", MAX_VERTICES);
        scanf("%d", &vertices);

        if (vertices < 6 || vertices > MAX_VERTICES) {
            printf("Quantidade invalida.\n");
        }
    } while (vertices < 6 || vertices > MAX_VERTICES);

    inicializarGrafo(grafo, vertices);

    printf("Digite o numero de ruas/arestas: ");
    scanf("%d", &arestas);

    for (i = 0; i < arestas; i++) {
        printf("\nAresta %d\n", i + 1);
        origem = lerVertice("Origem", vertices);
        destino = lerVertice("Destino", vertices);
        printf("Peso/distancia: ");
        scanf("%d", &peso);

        inserirAresta(grafo, origem, destino, peso);
    }
}

void exibirMenu(void) {
    printf("\n===== SISTEMA DE PLANEJAMENTO DE ROTAS =====\n");
    printf("1 - Exibir matriz de adjacencia\n");
    printf("2 - Cadastrar novo mapa\n");
    printf("3 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Grafo grafo;
    int opcao;

    carregarExemplo(&grafo);

    printf("Sistema iniciado com um mapa exemplo de 6 pontos: A, B, C, D, E e F.\n");
    printf("Use a opcao 2 se quiser cadastrar outro mapa.\n");

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMatriz(&grafo);
                break;

            case 2:
                cadastrarGrafo(&grafo);
                break;

            case 3:
                printf("Encerrando o sistema.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 3);

    return 0;
}

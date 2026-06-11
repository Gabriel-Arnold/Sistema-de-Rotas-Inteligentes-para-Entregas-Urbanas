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

void exibirPonto(int vertice) {
    printf("%c", 'A' + vertice);
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

void bfs(Grafo *grafo, int inicio) {
    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;
    int atual, i;

    if (inicio < 0 || inicio >= grafo->vertices) {
        printf("Vertice inicial invalido.\n");
        return;
    }

    visitado[inicio] = 1;
    fila[tras++] = inicio;

    printf("\nOrdem de visita BFS: ");

    while (frente < tras) {
        atual = fila[frente++];
        exibirPonto(atual);
        printf(" ");

        for (i = 0; i < grafo->vertices; i++) {
            if (grafo->matriz[atual][i] > 0 && !visitado[i]) {
                visitado[i] = 1;
                fila[tras++] = i;
            }
        }
    }

    printf("\nAplicacao: mostra os pontos alcancaveis a partir do ponto escolhido.\n");
}

void dfsRecursivo(Grafo *grafo, int atual, int visitado[]) {
    int i;

    visitado[atual] = 1;
    exibirPonto(atual);
    printf(" ");

    for (i = 0; i < grafo->vertices; i++) {
        if (grafo->matriz[atual][i] > 0 && !visitado[i]) {
            dfsRecursivo(grafo, i, visitado);
        }
    }
}

void dfs(Grafo *grafo, int inicio) {
    int visitado[MAX_VERTICES] = {0};

    if (inicio < 0 || inicio >= grafo->vertices) {
        printf("Vertice inicial invalido.\n");
        return;
    }

    printf("\nOrdem de visita DFS: ");
    dfsRecursivo(grafo, inicio, visitado);
    printf("\nAplicacao: ajuda a explorar a cobertura das rotas existentes.\n");
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
    printf("2 - Executar BFS\n");
    printf("3 - Executar DFS\n");
    printf("4 - Cadastrar novo mapa\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Grafo grafo;
    int opcao;
    int inicio;

    carregarExemplo(&grafo);

    printf("Sistema iniciado com um mapa exemplo de 6 pontos: A, B, C, D, E e F.\n");
    printf("Use a opcao 4 se quiser cadastrar outro mapa.\n");

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMatriz(&grafo);
                break;

            case 2:
                inicio = lerVertice("Vertice inicial para BFS", grafo.vertices);
                bfs(&grafo, inicio);
                break;

            case 3:
                inicio = lerVertice("Vertice inicial para DFS", grafo.vertices);
                dfs(&grafo, inicio);
                break;

            case 4:
                cadastrarGrafo(&grafo);
                break;

            case 5:
                printf("Encerrando o sistema.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    return 0;
}

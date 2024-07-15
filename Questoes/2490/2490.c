#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1100
typedef struct {
    int u, v;
    double w;
} Aresta;

int pai[MAXSIZE];
Aresta arestas[MAXSIZE];

int contadorAbastecimentos;
double limiteTempo;

int compararArestas(const void *a, const void *b) {
    double diferenca = ((Aresta *)a)->w - ((Aresta *)b)->w;
    if (diferenca == 0.0) return 0;
    else if (diferenca > 0.0) return 1;
    else return -1;
}

int encontrarPai(int vertice) {
    if (pai[vertice] == vertice) return vertice;
    return pai[vertice] = encontrarPai(pai[vertice]);
}

double kruskal(int numArestas, int numVertices) {
    double pesoTotal = 0;
    for (int i = 1; i <= numVertices; ++i) {
        pai[i] = i;
    }

    contadorAbastecimentos = 0;
    for (int i = 0; i < numArestas; ++i) {
        int pai1 = encontrarPai(arestas[i].u);
        int pai2 = encontrarPai(arestas[i].v);

        if (pai1 != pai2) {
            pai[pai1] = pai2;

            if (arestas[i].w > limiteTempo) {
                pesoTotal += arestas[i].w + 2;
                ++contadorAbastecimentos;
            } else {
                pesoTotal += arestas[i].w;
            }
        }
    }

    return pesoTotal;
}

int main() {
    int numQuarteiroes, numCaminhos;
    double tempoMaximo;

    while (scanf("%d %d %lf", &numQuarteiroes, &numCaminhos, &tempoMaximo), numQuarteiroes && numCaminhos && tempoMaximo) {
        limiteTempo = tempoMaximo;

        for (int i = 0; i < numCaminhos; ++i)
            scanf("%d %d %lf", &arestas[i].u, &arestas[i].v, &arestas[i].w);

        qsort(arestas, numCaminhos, sizeof(Aresta), compararArestas);
        printf("%.2lf ", kruskal(numCaminhos, numQuarteiroes));
        printf("%d\n", contadorAbastecimentos);
    }

    return 0;
}
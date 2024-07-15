#include <stdio.h>
#include <string.h>

#define MAX_FUNCIONARIOS 500 // quantidade máxima de funcionários
#define GERENCIA_DIRETA 1
#define SEM_GERENCIA 0

#define INICIO 0
#define ATUAL 1
#define CONCLUIDO 2
#define NENHUM -1

char matriz_adj[MAX_FUNCIONARIOS + 1][MAX_FUNCIONARIOS + 1]; // matriz de adjacências
int numero_funcionarios; // quantidade de funcionários
int status[MAX_FUNCIONARIOS + 1]; // status da visita do funcionário para DFS
int tempo_descoberta[MAX_FUNCIONARIOS + 1]; // tempo de descoberta na DFS
int tempo_termino[MAX_FUNCIONARIOS + 1]; // tempo de término na DFS
int antecessor[MAX_FUNCIONARIOS + 1]; // antecessor na árvore de busca
int tempo; // tempo corrente durante execução do algoritmo

int idades[MAX_FUNCIONARIOS + 1];
int idade;

void visita_dfs(int u) {
    status[u] = ATUAL;
    tempo++;
    tempo_descoberta[u] = tempo;

    int v;
    for (v = 1; v <= numero_funcionarios; v++) {
        if (matriz_adj[u][v] == GERENCIA_DIRETA) { // se v é adjacente a u
            if (status[v] == INICIO) {
                if (idades[v] < idade) idade = idades[v];
                antecessor[v] = u;
                visita_dfs(v);
            }
        }
    }

    status[u] = CONCLUIDO;
    tempo++;
    tempo_termino[u] = tempo;
}

void dfs(int funcionario) {
    idade = 1000;
    int u;
    for (u = 1; u <= numero_funcionarios; u++) {
        status[u] = INICIO;
        tempo_descoberta[u] = NENHUM;
        tempo_termino[u] = NENHUM;
        antecessor[u] = NENHUM;
    }

    tempo = 0;
    if (status[funcionario] == INICIO) {
        visita_dfs(funcionario);
    }
}

void imprimir_vetor(int vet[]) {
    int i;
    for (i = 1; i <= numero_funcionarios; i++) {
        printf("%d, ", vet[i]);
    }
    printf("\n");
}

void inicializar_matriz() {
    memset(matriz_adj, SEM_GERENCIA, sizeof(matriz_adj));
}

void trocar_gerencia(int funcionarioA, int funcionarioB) {
    int auxiliar, i;

    // Trocar linhas na matriz de adjacências
    for (i = 1; i <= numero_funcionarios; i++) {
        auxiliar = matriz_adj[funcionarioA][i];
        matriz_adj[funcionarioA][i] = matriz_adj[funcionarioB][i];
        matriz_adj[funcionarioB][i] = auxiliar;
    }

    // Trocar colunas na matriz de adjacências
    for (i = 1; i <= numero_funcionarios; i++) {
        auxiliar = matriz_adj[i][funcionarioA];
        matriz_adj[i][funcionarioA] = matriz_adj[i][funcionarioB];
        matriz_adj[i][funcionarioB] = auxiliar;
    }
}

int main() {
    int numero_de_pessoas, numero_de_relacoes, numero_de_instrucoes;
    int funcionario;
    
    while (scanf("%d %d %d", &numero_de_pessoas, &numero_de_relacoes, &numero_de_instrucoes) != EOF) {
        // Inicialização da matriz de adjacências e outros vetores
        inicializar_matriz();
        numero_funcionarios = numero_de_pessoas;

        int i, j;
        for (i = 1; i <= numero_de_pessoas; i++) {
            scanf("%d", &idades[i]);
        }

        int gerente, gerido;
        for (i = 1; i <= numero_de_relacoes; i++) {
            scanf("%d %d", &gerente, &gerido);
            matriz_adj[gerido][gerente] = GERENCIA_DIRETA;
        }

        char tipo_instrucao;
        for (i = 1; i <= numero_de_instrucoes; i++) {
            scanf(" %c", &tipo_instrucao);

            if (tipo_instrucao == 'P') {
                scanf("%d", &funcionario);
                dfs(funcionario);
                if (idade == 1000)
                    printf("*\n");
                else
                    printf("%d\n", idade);
            }
            if (tipo_instrucao == 'T') {
                scanf("%d %d", &gerente, &gerido);
                trocar_gerencia(gerente, gerido);
            }
        }
    }
    
    return 0;
}

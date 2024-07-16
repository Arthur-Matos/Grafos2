#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LOG 18
#define MAXSIZE 100005
#define INF 0x3f3f3f3fLLU

typedef long long ll;

typedef struct Node {
    int u, w;
    struct Node *next;
} Node;

typedef struct Graph {
    Node *adj;
} Graph;

int n;
ll dist[MAXSIZE];
int depth[MAXSIZE];
int parent[MAXSIZE][LOG];

Graph *createGraph(int size);
Node *createNode(int u, int w);
void addEdge(Graph *g, int v, int u, int w);
void preprocess();
void dfs(int s, Graph *g);
int findLCA(int u, int v);
void swap(int *a, int *b);

int main() {
    int u, v, w, q;
    while (scanf("%d%*c", &n), n) {
        Graph *g = createGraph(n + 1);
        for (int i = 1; i < n; ++i) {
            scanf("%d %d", &v, &w);
            addEdge(g, v, i, w);
        }

        for (int i = 0; i <= n; ++i)
            dist[i] = depth[i] = INF;
        parent[0][0] = depth[0] = dist[0] = 0;

        dfs(0, g);
        preprocess();

        scanf("%d", &q);
        while (q--) {
            scanf("%d %d", &u, &v);
            int lca = findLCA(u, v);
            ll answer = (dist[u] - dist[lca]) + (dist[v] - dist[lca]);
            printf("%lld%c", answer, q > 0 ? ' ' : '\n');
        }
    }
    return 0;
}

Graph *createGraph(int size) {
    Graph *g = malloc(sizeof(Graph));
    g->adj = malloc(sizeof(Node) * (size + 1));
    for (int i = 0; i <= size; ++i)
        g->adj[i].next = NULL;
    return g;
}

Node *createNode(int u, int w) {
    Node *node = malloc(sizeof(Node));
    node->u = u;
    node->w = w;
    node->next = NULL;
    return node;
}

void addEdge(Graph *g, int v, int u, int w) {
    Node *node = createNode(u, w);
    node->next = g->adj[v].next;
    g->adj[v].next = node;
}

void dfs(int s, Graph *g) {
    for (Node *i = g->adj[s].next; i; i = i->next) {
        int v = i->u, w = i->w;
        if (depth[v] == INF) {
            depth[v] = depth[s] + 1;
            dist[v] = dist[s] + w;
            parent[v][0] = s;
            dfs(v, g);
        }
    }
}

void preprocess() {
    for (int i = 1; i < LOG; ++i)
        for (int u = 0; u < n; ++u)
            parent[u][i] = parent[u][i - 1] != -1 ? parent[parent[u][i - 1]][i - 1] : -1;
}

int findLCA(int u, int v) {
    if (depth[u] > depth[v]) swap(&u, &v);
    for (int i = 0; i < LOG; i++)
        if ((depth[v] - depth[u]) >> i & 1)
            v = parent[v][i];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i)
        if (parent[u][i] != parent[v][i])
            u = parent[u][i], v = parent[v][i];
    return parent[u][0];
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

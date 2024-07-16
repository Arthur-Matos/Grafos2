#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int x,y;
} ponto;

typedef struct
{
    int v;
    int w;
} Edge;

Edge EDGE(int, int);

Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

typedef struct graph *Graph;

Graph GRAPHInit(int); // int é quant de vertices
void GRAPHInsertE(Graph, Edge);
void GRAPHRemoveE(Graph, Edge);
int GRAPHEdges(Edge[], Graph G);
Graph GRAPHCopy(Graph);
void GRAPHDestroy(Graph);
int **MATRIXInit(int, int, int);
void GRAPHshowTC(Graph);

struct graph
{
    int V;
    int E;
    int **adj;
    int **tc;
};

Graph GRAPHInit(int v)
{
    Graph G = malloc(sizeof(*G));
    G->V = v;
    G->E = 0;
    G->adj = MATRIXInit(v, v, 0);
    return G;
}

void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v;
    int w = e.w;

    if (G->adj[v][w] == 0)
        G->E++;

    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
}

void GRAPHDestroy(Graph G)
{
    int v;

    for (v = 0; v < G->V; v++)
    {
        free(G->adj[v]);
    }

    free(G->adj);

    free(G);
}

int **MATRIXInit(int r, int c, int val)
{
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

#define vertex Edge

static vertex *queue;
static int begin, end;

void QUEUEinit(int N)
{
    queue = malloc(N * sizeof(vertex));
    begin = end = 0;
}

int QUEUEempty(void)
{
    return begin == end;
}

void QUEUEput(vertex v)
{
    queue[end++] = v;
}

vertex QUEUEget(void)
{
    return queue[begin++];
}

void QUEUEfree(void)
{
    free(queue);
}

#define INT_MAX 2147483647

#define maxV 5002

static int pred[maxV], visited[maxV], dist[maxV], cnt = 0;

int GRAPHbfs(Graph G, Edge e)
{
    int v, w;
    vertex x;
    QUEUEinit(G->V);
    for (v = 0; v < G->V; v++)
    {
        visited[v] = 0;
        dist[v] = INT_MAX;
        pred[v] = -1;
    }
    QUEUEput(e);
    visited[e.v] = 1;
    dist[e.v] = 0;
    while (!QUEUEempty())
    {
        x = QUEUEget();
        v = x.v;
        for (w = 0; w < G->V; w++)
        {
            if (G->adj[v][w] == 1)
            {
                if (visited[w] == 0)
                {
                    visited[w] = 1;
                    dist[w] = dist[v] + 1;
                    pred[w] = v;
                    QUEUEput(EDGE(w, v));

                    if (w == e.w)
                    {
                        QUEUEfree();
                        return 1;
                    }
                }
            }
        }
    }
    QUEUEfree();
    return 0;
}

int main(){


    int d, n, ox, oy, sx, sy;

    scanf("%d", &d);
    scanf("%d", &n);

    Graph G = GRAPHInit(n);

    ponto *pontos = malloc(n*sizeof(ponto));

    for(int i=0; i<n; i++){
        int x, y;
        scanf("%d %d", &x, &y);

        pontos[i].x = x;
        pontos[i].y = y;        

    }

    // Euclidean distance between all points

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i!=j){
                int distx = pontos[i].x - pontos[j].x;
                int disty = pontos[i].y - pontos[j].y;
                double dist = sqrt(distx*distx + disty*disty);
                if(dist <= d){
                    GRAPHInsertE(G, EDGE(i, j));
                }
            }
        }
    }

    int conn = GRAPHbfs(G, EDGE(0, 1));

    if (conn){
        printf("%d\n", dist[1]);
    }
    else{
        printf("-1\n");
    }

    return 0;
}
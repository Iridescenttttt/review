#include<stdio.h>
#include<stdlib.h>

#define INFINITY INT_MAX
#define MAX_V 20
#define ElemType char

int visit[MAX_V];

typedef struct Vertex{
    int code;
    ElemType info;
}Vertex;

typedef struct ArcNode{
    int adjvex;
    int weight;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VexNode{
    Vertex data;
    ArcNode *firstarc;
}VexNode;

typedef struct ALGraph{
    VexNode VN[MAX_V];
    int vexnum, arcnum;
    Vertex vexs[MAX_V];
}ALGraph;

// void CreateGraph(ALGraph *G)                                    //无向图
// {
//     scanf("%d%d", &G->vexnum, &G->arcnum);
//     getchar();
//     for(int i = 0; i < G->vexnum; i++){
//         G->vexs[i].code = i;
//         scanf("%c", &G->vexs[i].info);
//     }
//     for(int i = 0; i < G->vexnum; i++){
//         G->VN[i].firstarc = NULL;
//     }
//     ArcNode *p;
//     for(int k = 0; k < G->arcnum; k++){
//         int i, j;
//         scanf("%d%d", &i, &j);
//         p = (ArcNode*)malloc(sizeof(ArcNode));
//         p->adjvex = j;
//         p->nextarc = G->VN[i].firstarc;
//         G->VN[i].firstarc = p;
//         p = (ArcNode*)malloc(sizeof(ArcNode));
//         p->adjvex = i;
//         p->nextarc = G->VN[j].firstarc;
//         G->VN[j].firstarc = p;
//     }
// }

// void CreateGraph(ALGraph *G)                                    //有向图
// {
//     scanf("%d%d", &G->vexnum, &G->arcnum);
//     getchar();
//     for(int i = 1; i <= G->vexnum; i++){
//         G->vexs[i].code = i;
//         scanf("%c", &G->vexs[i].info);
//     }
//     for(int i = 1; i <= G->vexnum; i++){
//         G->VN[i].firstarc = NULL;
//     }
//     ArcNode *p;
//     for(int k = 0; k < G->arcnum; k++){
//         int i, j;
//         scanf("%d%d", &i, &j);
//         p = (ArcNode*)malloc(sizeof(ArcNode));
//         p->adjvex = j;
//         p->nextarc = G->VN[i].firstarc;
//         G->VN[i].firstarc = p;
//     }
// }

void CreateGraph(ALGraph *G)                                    //无向网
{
    scanf("%d%d", &G->vexnum, &G->arcnum);
    getchar();
    for(int i = 0; i < G->vexnum; i++){
        G->vexs[i].code = i;
        scanf("%c", &G->vexs[i].info);
    }
    for(int i = 0; i < G->vexnum; i++){
        G->VN[i].firstarc = NULL;
    }
    ArcNode *p;
    for(int k = 0; k < G->arcnum; k++){
        int i, j, w;
        scanf("%d%d%d", &i, &j, &w);
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->weight = w;
        p->adjvex = j;
        p->nextarc = G->VN[i].firstarc;
        G->VN[i].firstarc = p;
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = i;
        p->weight = w;
        p->nextarc = G->VN[j].firstarc;
        G->VN[j].firstarc = p;
    }
}

// void CreateGraph(ALGraph *G)                                       //有向网
// {
//     scanf("%d%d", &G->vexnum, &G->arcnum);
//     getchar();
//     for(int i = 1; i <= G->vexnum; i++){
//         G->vexs[i].code = i;
//         scanf("%c", &G->vexs[i].info);
//     }
//     for(int i = 1; i <= G->vexnum; i++){
//         G->VN[i].firstarc = NULL;
//     }
//     ArcNode *p;
//     for(int k = 0; k < G->arcnum; k++){
//         int i, j, w;
//         scanf("%d%d%d", &i, &j, &w);
//         p = (ArcNode*)malloc(sizeof(ArcNode));
//         p->weight = w;
//         p->adjvex = j;
//         p->nextarc = G->VN[i].firstarc;
//         G->VN[i].firstarc = p;
//     }
// }

void DFS(ALGraph G, int index)
{
    ArcNode *p;
    visit[index] = 1;
    printf("%c ", G.vexs[index].info);
    p = G.VN[index].firstarc;
    while(p){
        if(!visit[p->adjvex])DFS(G, p->adjvex);
        p = p->nextarc;
    }
}

void DFS_Visit(ALGraph G)
{
    for(int i = 0; i < G.vexnum; i++){
        visit[i] = 0;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(!visit[i])DFS(G, i);
    }
}

void BFS(ALGraph G, int index)
{
    ArcNode *p;
    int queue[MAX_V];
    int front = 0, rear = 0;
    queue[rear++] = index;
    visit[index] = 1;
    while(front != rear){
        int i = queue[front];
        front = (front + 1) % MAX_V;
        printf("%c ", G.vexs[i].info);
        p = G.VN[i].firstarc;
        while(p){
            if(!visit[p->adjvex]){
                queue[rear] = p->adjvex;
                rear = (rear + 1) % MAX_V;
                visit[p->adjvex] = 1;
            }
            p = p->nextarc;
        }
    }
}

void BFS_Visit(ALGraph G)
{
    for(int i = 0; i < G.vexnum; i++){
        visit[i] = 0;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(!visit[i])BFS(G, i);
    }
}

void FindPath(ALGraph G, int u, int v, int *path, int d)
{
    ArcNode *p;
    path[d] = u;
    visit[u] = 1;
    if(u == v){
        for(int i = 0; i <= d; i++){
            if(i != d)printf("%c->", G.vexs[path[i]].info);
            else printf("%c\n", G.vexs[path[i]].info);
        }
    }
    else{
        p = G.VN[u].firstarc;
        while(p){
            if(!visit[p->adjvex]){
                FindPath(G, p->adjvex, v, path, d + 1);
                visit[p->adjvex] = 0;
            }
            p = p->nextarc;
        }
    }
}

void Prim(ALGraph G, int v)
{
    int vexcode[MAX_V];
    int lowcost[MAX_V];
    for(int i = 0; i < G.vexnum; i++){
        vexcode[i] = v;
        lowcost[i] = INFINITY;
    }
    lowcost[v] = 0;
    ArcNode *p = G.VN[v].firstarc;
    while(p){
        lowcost[p->adjvex] = p->weight;
        p = p->nextarc;
    }
    for(int i = 1; i < G.vexnum; i++){
        int min = INFINITY, k;
        for(int j = 0; j < G.vexnum; j++){
            if(lowcost[j] && lowcost[j] < min){
                min = lowcost[j];
                k = j;
            }
        }
        printf("边（%d,%d）权为：%d\n", k, vexcode[k], min);
        lowcost[k] = 0;
        p = G.VN[k].firstarc;
        while(p){
            if(p->weight < lowcost[p->adjvex]){
                lowcost[p->adjvex] = p->weight;
                vexcode[p->adjvex] = k;
            }
            p = p->nextarc;
        }
    }
}

int main()
{
    ALGraph G;
    CreateGraph(&G);
    // DFS_Visit(G);
    // BFS_Visit(G);
    // int *path = (int*)malloc(MAX_V * sizeof(int));
    // FindPath(G, 0, 3, path, 0);
    Prim(G, 0);
    return 0;
}


/*
无向图：
4 5
abcd
0 1
0 2
1 2
1 3
2 3
*/

/*
有向图：
4 5
abcd
1 2
1 3
2 3
2 4
3 4
*/

/*
无向网：
4 5
abcd
0 1 4
0 2 7
1 2 5
1 3 6
2 3 8
*/

/*
有向网：
4 5
abcd
1 2 4
1 3 7
2 3 5
2 4 6
3 4 8
*/
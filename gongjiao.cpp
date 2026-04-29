#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 30
int visited[MAX_VERTEX_NUM];
typedef char VertexType;
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    int info;
} ArcNode;
typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
} VNode;
typedef struct
{
    VNode adjlist[MAX_VERTEX_NUM];
    int vexnum, arcnum;
}ALGraph;
int LocateVex(ALGraph G, VertexType v)
{
    int i;
    for (i=0;i<G.vexnum; ++i)
        if (G.adjlist[i].data == v)
            return i;
    return -1;
}

void CreateALGraph(ALGraph *G)
{
    int i,j,k;
    VertexType v1,v2;
    ArcNode *p1, *p2;
    printf("请输入总顶点数，总边数，以空格隔开:\n");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    printf("\n输入每个顶点的数据，如A \n");
    //创建存放表头结点的一维数组
    for(i=0;i<G->vexnum; ++i)
    {
        fflush(stdin);
        printf("请输入第%d个顶点的数据:\n", i+1);
        scanf(" %c", &G->adjlist[i].data);
        G->adjlist[i].firstarc = NULL;
    }
    printf("\n输入边依附的顶点,如A,B\n");
    for(k=0;k<G->arcnum; ++k)
    {
        fflush(stdin);
        printf("请输入第%d条边依附的顶点:\n", k+1);
        scanf(" %c %c", &v1, &v2);
        i=LocateVex(*G, v1);
        j=LocateVex(*G, v2);
        p1=(ArcNode*)malloc(sizeof(ArcNode));
        p1->adjvex=j;
        p1->nextarc=G->adjlist[i].firstarc;
        G->adjlist[i].firstarc=p1;
        p2=(ArcNode*)malloc(sizeof(ArcNode));
        p2->adjvex=i;
        p2->nextarc=G->adjlist[j].firstarc;
        G->adjlist[j].firstarc=p2;
    }
}
void PrintPath(ALGraph G, int *path, int pathLen)
{
    int i;
    for(i=0;i<pathLen;i++)
        printf("%c ", G.adjlist[path[i]].data);
    printf("\n");
}
void FindPath(ALGraph G, int start, int end, int *path, int pathLen)
{
    path[pathLen]=start;
    pathLen++;
    if(start == end)
        PrintPath(G, path, pathLen);
        else
        {
            ArcNode *p;
            visited[start] = 1;
            p=G.adjlist[start].firstarc;
            while(p)
            {
                if(visited[p->adjvex]==0)
                {
                    FindPath(G, p->adjvex, end, path, pathLen);
                    visited[p->adjvex] = 0;
                }
                p=p->nextarc;
            }
        }
        pathLen--;
}
int main()
{
    ALGraph G;
    VertexType v1,v2;
    int i,j,v;
    int path[MAX_VERTEX_NUM];
    CreateALGraph(&G);
    fflush(stdin);
    printf("请输入要搜索的公交线路的两个顶点:");
    scanf(" %c %c", &v1, &v2);
    i=LocateVex(G, v1);
    j=LocateVex(G, v2);
    for(v=0;v<G.vexnum;v++)
        visited[v]=0;
    FindPath(G, i, j, path, 0);
    return 0;
}

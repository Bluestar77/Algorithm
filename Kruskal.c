#include <stdio.h>
#include <stdlib.h>

//Prim 알고리즘 (최소신장트리)

#define FALSE 0
#define TRUE 1
#define INF 100

typedef struct Edge
{
    char v1, v2;
    int weight;
    struct Edge* next;
}Edge;

typedef struct IncidentEdge
{
    char aName;
    Edge* e;
    struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex
{
    char vName;
    int isVisit;
    IncidentEdge* iHead;
    struct Vertex* next;
}Vertex;

typedef struct
{
    Vertex* vHead;
    Edge* eHead;
    int eCount, vCount;
}GraphType;

void init(GraphType* G)
{
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;
}

void makeVertex(GraphType* G, char vName)
{
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->vName = vName;
    v->isVisit = FALSE;
    v->iHead = NULL;
    v->next = NULL;

    G->vCount++;

    Vertex* p = G->vHead;
    if (p == NULL)
        G->vHead = v;
    else
    {
        while (p->next != NULL)
            p = p->next;
        p->next = v;
    }
}

void makeIncidentEdge(Vertex* v, char aName, Edge* e)
{
    IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
    p->aName = aName;
    p->e = e;
    p->next = NULL;
    IncidentEdge* q = v->iHead;
    if (q == NULL)
        v->iHead = p;
    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = p;
    }
}

Vertex* findVertex(GraphType* G, char vName)
{
    Vertex* v = G->vHead;
    while (v->vName != vName)
        v = v->next;

    return v;
}

void insertEdge(GraphType* G, char v1, char v2, int w)
{
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->weight = w;
    e->next = NULL;
    G->eCount++;

    Edge* p = G->eHead;
    if (p == NULL)
        G->eHead = e;
    else
    {
        while (p->next != NULL)
            p = p->next;
        p->next = e;
    }

    Vertex* v = findVertex(G, v1);
    makeIncidentEdge(v, v2, e);
    v = findVertex(G, v2);
    makeIncidentEdge(v, v1, e);
}


void print(GraphType* G)
{
    Vertex* p = G->vHead;
    IncidentEdge* q;
    for (; p != NULL; p = p->next)
    {
        printf("[%c] : ", p->vName);
        for (q = p->iHead; q != NULL; q = q->next)
            printf("[%c, %d] ", q->aName, q->e->weight);
        printf("\n");
    }

    printf("\n");
}

void incSort(GraphType* G, Edge* e[])  //가중치로 정렬
{
    int i, min;
    Edge* p = G->eHead;
    for (i = 0; i < G->eCount; i++) {
        e[i] = p;
        p = p->next;
    }

    for (i = 0; i < G->eCount - 1; i++) {
        min = i;
        for (int j = i + 1; j < G->eCount; j++) {
            if (e[j]->weight < e[min]->weight)
                min = j;
        }
        p = e[min];
        e[min] = e[i];
        e[i] = p;
    }
    for (i = 0; i < G->eCount; i++) {
        printf("[%c%c%d] ", e[i]->v1, e[i]->v2, e[i]->weight);
    }
    printf("\n");
}

int rFind(int v[], int vNum)
{
    if (v[vNum] == -1)
        return vNum;

    while (v[vNum] != -1)
    {
        vNum = v[vNum];
    }
    return vNum;
}

void vUnion(int v[], int vNum1, int vNum2)
{
    int r1 = rFind(v, vNum1);
    int r2 = rFind(v, vNum2);

    v[r2] = r1;
}

void kruskal(GraphType* G, Edge* e[], int v[])
{
    int eCnt = 0, i = 0;
    int vNum1, vNum2;
    Edge* p;

    while (eCnt < G->vCount - 1)
    {
        p = e[i];  //가중치 제일 작았던 간선
        vNum1 = rFind(v, p->v1 - 97); //루트를 찿아준다
        vNum2 = rFind(v, p->v2 - 97);

        if (vNum1 != vNum2)
        {
            eCnt++;
            printf("%d : [% c % c % d]\n", eCnt, p->v1, p->v2, p->weight);
            vUnion(v, vNum1, vNum2);
        }
        i++;
    }
}

int main()
{
    GraphType G;
    init(&G);

    makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
    makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
    makeVertex(&G, 'g');

    insertEdge(&G, 'a', 'b', 29); insertEdge(&G, 'a', 'f', 10);
    insertEdge(&G, 'b', 'c', 16); insertEdge(&G, 'b', 'g', 15);
    insertEdge(&G, 'c', 'd', 12); insertEdge(&G, 'd', 'g', 18);
    insertEdge(&G, 'd', 'e', 22); insertEdge(&G, 'e', 'f', 27);
    insertEdge(&G, 'e', 'g', 25);

    print(&G);

    /Edge* e[20];
    incSort(&G, e);  //가중치 크기 오름차순으로 Edge정렬

    int v[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    //v[] 정점의 루트 ( 같은게 있으면 싸이클이 있다고 판단)
    kruskal(&G, e, v);
   

    return 0;
}
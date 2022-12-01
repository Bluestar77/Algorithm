#include stdio.h
#include stdlib.h

다익크트라 알고리즘

#define FALSE 0
#define TRUE 1 
#define INF 1000
#define N 20

int dist[N];
int visit[N];

typedef struct Edge
{
    char v1, v2;
    int weight;
    struct Edge next;
}Edge;

typedef struct IncidentEdge
{
    char aName;
    Edge e;
    struct IncidentEdge next;
}IncidentEdge;

typedef struct Vertex
{
    char vName;
    int isVisit;
    IncidentEdge iHead;
    struct Vertex next;
}Vertex;

typedef struct
{
    Vertex vHead;
    Edge eHead;
    int eCount, vCount;
}GraphType;

void init(GraphType G)
{
    G - vHead = NULL;
    G - eHead = NULL;
    G - vCount = G - eCount = 0;

    for (int i = 0; i N; i++) {
        dist[i] = INF;
        visit[i] = FALSE;
    }
}

void makeVertex(GraphType G, char vName)
{
    Vertex v = (Vertex)malloc(sizeof(Vertex));
    v - vName = vName;
    v - isVisit = FALSE;
    v - iHead = NULL;
    v - next = NULL;

    G - vCount++;

    Vertex p = G - vHead;
    if (p == NULL)
        G - vHead = v;
    else
    {
        while (p - next != NULL)
            p = p - next;
        p - next = v;
    }
}

void makeIncidentEdge(Vertex v, char aName, Edge e)
{
    IncidentEdge p = (IncidentEdge)malloc(sizeof(IncidentEdge));
    p - aName = aName;
    p - e = e;
    p - next = NULL;
    IncidentEdge q = v - iHead;
    if (q == NULL)
        v - iHead = p;
    else
    {
        while (q - next != NULL)
            q = q - next;
        q - next = p;
    }
}

Vertex findVertex(GraphType G, char vName)
{
    Vertex v = G - vHead;
    while (v - vName != vName)
        v = v - next;

    return v;
}

void insertEdge(GraphType G, char v1, char v2, int w)
{
    Edge e = (Edge)malloc(sizeof(Edge));
    e - v1 = v1;
    e - v2 = v2;
    e - weight = w;
    e - next = NULL;
    G - eCount++;

    Edge p = G - eHead;
    if (p == NULL)
        G - eHead = e;
    else
    {
        while (p - next != NULL)
            p = p - next;
        p - next = e;
    }

    Vertex v = findVertex(G, v1);
    makeIncidentEdge(v, v2, e);
    v = findVertex(G, v2);
    makeIncidentEdge(v, v1, e);
}


void print(GraphType G)
{
    Vertex p = G - vHead;
    IncidentEdge q;
    for (; p != NULL; p = p - next)
    {
        printf([% c], p - vName);
        for (q = p - iHead; q != NULL; q = q - next)
            printf([% c, % d], q - aName, q - e - weight);
        printf(n);
    }

    printf(n);
}

int findMin(GraphType G)
{
    int min = INF  2;
    int minIdx;

    for (int i = 0; i G - vCount; i++) {
        if (dist[i]  min && visit[i] == FALSE)
        {
            min = dist[i];
            minIdx = i;
        }
    }

    return minIdx;
}

void dijkstra(GraphType G, char s)
{
    Vertex p = findVertex(G, s);
    IncidentEdge q;
    int u;

    dist[s - 97] = 0;
    visit[s - 97] = TRUE;
    printf(% c[% d], s, dist[s]);

    for (q = p - iHead; q != NULL; q = q - next) {
        dist[q - aName - 97] = q - e - weight;
    }


    for (int i = 0; i G - vCount - 1; i++) {
        u = findMin(G); 정점과 연결된 간선 가중치 중 젤 작은값(visit안한것 중)
            p = findVertex(G, u + 97);
        visit[u] = TRUE;
        printf(% c[% d], p - vName, dist[u]);

        for (q = p - iHead; q != NULL; q = q - next)
        {
            if (visit[q - aName - 97] == FALSE) {
                if (dist[u] + q - e - weight  dist[q - aName - 97]) {
                    dist[q - aName - 97] = dist[u] + q - e - weight;
                }
            }
        }
    }
}


int main()
{
    GraphType G;
    init(&G);

    makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
    makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
    makeVertex(&G, 'g');

    insertEdge(&G, 'a', 'b', 7); insertEdge(&G, 'a', 'e', 3);
    insertEdge(&G, 'a', 'f', 10); insertEdge(&G, 'b', 'c', 4);
    insertEdge(&G, 'b', 'd', 10); insertEdge(&G, 'b', 'e', 2);
    insertEdge(&G, 'b', 'f', 6); insertEdge(&G, 'c', 'd', 2);
    insertEdge(&G, 'd', 'e', 11); insertEdge(&G, 'd', 'f', 9);
    insertEdge(&G, 'd', 'g', 4); insertEdge(&G, 'e', 'g', 5);

    print(&G);

    dijkstra(&G, 'a');

    return 0;
}

#include <algorithm>
#include <set>
#include <string>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <map>
#include <list>
#include <queue>

#define MAX_NODES 1010

using namespace std;

// Definindo tipos para tornar o código mais legível.
typedef vector<int> VectorInt;
typedef pair<int, int> PairInt;
typedef vector<PairInt> VectorPairInt;

// Declaração das variáveis globais.
VectorInt dfsStack;
int numVertices, numEdges, parent[MAX_NODES], low[MAX_NODES], num[MAX_NODES], visited[MAX_NODES];
int result, nodeCounter, completeFlag, bridgeFlag;

// Declaração de gráficos direcionados e não direcionados.
vector<VectorInt> directedGraph(MAX_NODES), undirectedGraph(MAX_NODES);

typedef struct UnionFindSet {
    int parent, rank;
}UnionFindSet;

UnionFindSet nodeSet[MAX_NODES];

// Função para ler um número inteiro da entrada padrão.
int readInt()
{
    bool isNegative = false;
    int result = 0;
    char ch = getchar_unlocked();
    while (true) {
        if (ch == '-')
            break;
        if (ch >= '0' && ch <= '9')
            break;
        ch = getchar_unlocked();
    }
    if (ch == '-')
        isNegative = true;
    else
        result = ch - '0';
    while (true) {
        ch = getchar_unlocked();
        if (ch < '0' || ch > '9')
            break;
        result = result * 10 + (ch - '0');
    }
    if (isNegative)
        return -result;
    else
        return result;
}

// Função para inicializar as variáveis antes de executar os algoritmos.
void initialize()
{
    for (int i = 0; i < numVertices; ++i) {
        nodeSet[i].parent = i;
        nodeSet[i].rank = visited[i] = 0;
        parent[i] = low[i] = num[i] = 0;
        directedGraph[i].clear();
        undirectedGraph[i].clear();
    }
}

// Função para ligar dois nós na estrutura UnionFindSet.
void linkNodes(int x, int y)
{
    if (nodeSet[x].rank > nodeSet[y].rank)
        nodeSet[y].parent = x;
    else {
        nodeSet[x].parent = y;
        if (nodeSet[x].rank == nodeSet[y].rank)
            nodeSet[y].rank = nodeSet[y].rank + 1;
    }
}

// Função para encontrar o conjunto ao qual um nó pertence na estrutura UnionFindSet.
int findSet(int x)
{
    while (nodeSet[x].parent != x)
        x = nodeSet[x].parent;
    return x;
}

// Função para unir dois conjuntos na estrutura UnionFindSet.
void unionSet(int x, int y)
{
    linkNodes(findSet(x), findSet(y));
}

// Função para verificar se dois nós estão no mesmo conjunto na estrutura UnionFindSet.
bool isSameSet(int x, int y)
{
    return findSet(x) == findSet(y);
}

// Implementação do algoritmo de Tarjan para encontrar componentes fortemente conectados.
void tarjanAlgorithm(int u)
{
    low[u] = num[u] = nodeCounter++;
    dfsStack.push_back(u);
    visited[u] = true;
    VectorInt::iterator iter;
    for (iter = directedGraph[u].begin(); iter != directedGraph[u].end(); ++iter) {
        if (!num[*iter])
            tarjanAlgorithm(*iter);
        if (visited[*iter])
            low[u] = min(low[u], low[*iter]);
    }
    if (low[u] == num[u]) {
        int resp = 0;
        while (true) {
            int vertex = dfsStack.back();
            dfsStack.pop_back();
            resp++;
            if (u ==

 vertex)
                break;
        }
        if (resp == numVertices)
            completeFlag = true;
    }
}

// Função para encontrar pontos de articulação em um gráfico.
void findArticulationPoints(int u)
{
    VectorInt::iterator iter;
    low[u] = num[u] = nodeCounter++;
    for (iter = undirectedGraph[u].begin(); iter != undirectedGraph[u].end(); ++iter) {
        if (!num[*iter]) {
            result++;
            parent[*iter] = u;
            findArticulationPoints(*iter);
            if (low[*iter] > num[u])
                if (isSameSet(u, *iter))
                    bridgeFlag = true;
            low[u] = min(low[u], low[*iter]);
        } else if (*iter != parent[u])
            low[u] = min(low[u], num[*iter]);
    }
}

int main()
{
    int nodeA, nodeB, edgeType;
    while (scanf("%d %d", &numVertices, &numEdges) != EOF) {
        initialize();
        result = nodeCounter = completeFlag = bridgeFlag = nodeCounter = 0;
        nodeA = readInt();
        nodeB = readInt();
        edgeType = readInt();
        for (int i = 0; i < numEdges-1; ++i) {
            nodeA = readInt();
            nodeB = readInt();
            edgeType = readInt();
            directedGraph[nodeA-1].push_back(nodeB-1);
            undirectedGraph[nodeA-1].push_back(nodeB-1);
            undirectedGraph[nodeB-1].push_back(nodeA-1);
            if (edgeType == 2)
                directedGraph[nodeB-1].push_back(nodeA-1);
            else
                unionSet(nodeB-1,nodeA-1);
        }
        tarjanAlgorithm(0);
        if (completeFlag)
            printf("-\n");
        else {
            for (int i = 0; i < numVertices; ++i)
                low[i] = num[i] = 0;
            nodeCounter = 0;
            findArticulationPoints(0);
            if (result != numVertices)
                printf("*\n");
            else {
                if (bridgeFlag)
                    printf("2\n");
                else
                    printf("1\n");
            }
        }
    }
    return 0;
}
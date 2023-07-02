#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int pai[MAXN], altura[MAXN];

// Inicializa o conjunto
void make_set(int n) {
    for (int i = 0; i < n; i++) {
        pai[i] = i;
        altura[i] = 0;
    }
}

// Busca o representante do conjunto de x
int find_set(int x) {
    if (x == pai[x])
        return x;
    return pai[x] = find_set(pai[x]);
}

// Une os conjuntos de x e y
void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (altura[x] < altura[y])
            swap(x, y);
        pai[y] = x;
        if (altura[x] == altura[y])
            altura[x]++;
    }
}

// Checa se x e y pertencem ao mesmo conjunto
bool same_set(int x, int y) {
    return find_set(x) == find_set(y);
}

// Estrutura para representar uma aresta
struct Aresta {
    int u, v, peso;
    bool operator<(const Aresta& a) const {
        return peso < a.peso;
    }
};

Aresta arestas[MAXN];

// Algoritmo de Kruskal para encontrar a árvore geradora mínima
int kruskal(int n, int m) {
    int valor = 0;
    make_set(n);
    sort(arestas, arestas + m);
    for (int i = 0; i < m; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;
        if (!same_set(u, v)) {
            union_sets(u, v);
            valor += peso;
        }
    }
    return valor;
}

int main() {
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        for (int i = 0; i < m; i++) {
            int u, v, peso;
            cin >> u >> v >> peso;
            arestas[i] = {u, v, peso};
        }
        int valorT = 0;
        for (int i = 0; i < m; i++) {
            valorT += arestas[i].peso;
        }
        int valor = kruskal(n, m);
        cout << valorT - valor << endl;
    }
    return 0;
}

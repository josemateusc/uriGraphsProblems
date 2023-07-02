#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1005;

vector<int> adj[MAXN];
int indeg[MAXN];
int time_to_compile[MAXN];

int main() {
    int n;

    while (cin >> n) {
        memset(indeg, 0, sizeof(indeg));
        memset(time_to_compile, 0, sizeof(time_to_compile));

        // Lê as dependências entre os arquivos
        for (int i = 1; i <= n; i++) {
            int m;
            cin >> m;
            while (m--) {
                int j;
                cin >> j;
                adj[j].push_back(i); // j depende de i
                indeg[i]++;
            }
            time_to_compile[i] = 1; // tempo de compilação é 1 minuto
        }

        // Ordenação topológica para determinar a ordem de compilação dos arquivos
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        int max_time = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                indeg[v]--;
                time_to_compile[v] = max(time_to_compile[v], time_to_compile[u] + 1);
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
            max_time = max(max_time, time_to_compile[u]);
        }

        // Verifica se é possível compilar todos os arquivos
        bool possible = true;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] > 0) {
                possible = false;
                break;
            }
        }

        if (possible) {
            cout << max_time << endl;
        } else {
            cout << -1 << endl;
        }

        // Limpa as estruturas para o próximo caso de teste
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}

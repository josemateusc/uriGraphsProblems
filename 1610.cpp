#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e4 + 5;
vector<int> grafo[MAXN];
bool visitado[MAXN], pilha_recursao[MAXN];

bool dfs(int v) {
    visitado[v] = true;
    pilha_recursao[v] = true;

    for (int u : grafo[v]) {
        if (!visitado[u]) {
            if (dfs(u))
                return true;
        } else if (pilha_recursao[u])
            return true;
    }

    pilha_recursao[v] = false;
    return false;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        for (int i = 1; i <= N; i++)
            grafo[i].clear();

        for (int i = 1; i <= M; i++) {
            int A, B;
            cin >> A >> B;
            grafo[A].push_back(B);
        }

        bool tem_loop = false;

        for (int i = 1; i <= N; i++) {
            visitado[i] = false;
            pilha_recursao[i] = false;
        }

        for (int i = 1; i <= N; i++) {
            if (!visitado[i]) {
                if (dfs(i)) {
                    tem_loop = true;
                    break;
                }
            }
        }

        if (tem_loop)
            cout << "SIM" << endl;
        else
            cout << "NAO" << endl;
    }

    return 0;
}

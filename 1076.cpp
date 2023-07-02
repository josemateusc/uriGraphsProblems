#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAX_V = 49;
vector<int> graph[MAX_V];

void addEdge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

int dfs(int start) {
    bool visited[MAX_V] = {false};
    int time = 0;
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while(!s.empty()) {
        int u = s.top();
        s.pop();
        time++;

        for(int v : graph[u]) {
            if(!visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }

    return time*2;
}

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        int N, V, A;
        cin >> N >> V >> A;

        for(int i = 0; i < V; i++) {
            graph[i].clear();
        }

        for(int i = 0; i < A; i++) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }

        int time = dfs(N);
        int result = time-2;
        cout << result << endl;
    }

    return 0;
}

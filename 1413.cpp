#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAXN = 211;
const double INF = 1e9;
const double EPS = 1e-9;

using namespace std;
using di = pair<double, int>;

vector<int> graph[MAXN];
int n, m, V, capacity[MAXN][MAXN], previous[MAXN];
double cost[MAXN][MAXN], speed[MAXN], X[MAXN], Y[MAXN], dist[MAXN];

bool Dijkstra()
{
    for (int i = 0; i <= V; i++)
    {
        dist[i] = INF;
        previous[i] = -1;
    }

    dist[0] = 0;
    previous[0] = 0;

    priority_queue<di, vector<di>, greater<di>> SSSP;
    SSSP.push(make_pair(0.0, 0));

    while (!SSSP.empty())
    {
        di current = SSSP.top();
        SSSP.pop();

        double covered = current.first;
        int v = current.second;

        if (dist[v] > covered + EPS)
            continue;
        if (v == V)
            break;

        for (int u : graph[v])
        {
            if (dist[v] + cost[v][u] + EPS <= dist[u] && capacity[v][u] > 0)
            {
                dist[u] = dist[v] + cost[v][u];
                previous[u] = v;
                SSSP.push(make_pair(dist[u], u));
            }
        }
    }

    if (dist[V] == INF)
        return false;

    vector<int> path;
    path.push_back(V);
    int current = V;

    while (current != 0)
    {
        path.push_back(previous[current]);
        current = previous[current];
    }

    reverse(path.begin(), path.end());
    int min_capacity = MAXN;

    for (int i = 0; i + 1 < path.size(); i++)
    {
        min_capacity = min(min_capacity, capacity[path[i]][path[i + 1]]);
    }

    for (int i = 0; i + 1 < path.size(); i++)
    {
        capacity[path[i]][path[i + 1]] -= min_capacity;
        capacity[path[i + 1]][path[i]] += min_capacity;
    }

    return true;
}

double EdmondKarp()
{
    double total = 0.0;

    while (true)
    {
        if (!Dijkstra())
            break;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j : graph[i])
        {
            if (capacity[i][j] < 1)
                total += cost[i][j];
        }
    }

    return total;
}

int main()
{
    while (scanf("%d %d", &n, &m) && (n || m))
    {
        for (int i = 0; i <= MAXN; i++)
        {
            graph[i].clear();
        }

        memset(capacity, 0, sizeof(capacity));
        V = n + m + 1;

        for (int i = 1; i <= n; i++)
        {
            graph[i].push_back(0);
            graph[0].push_back(i);
            capacity[0][i] = 1;
            cost[i][0] = cost[0][i] = 0.0;
        }

        for (int i = n + 1; i <= n + m; i++)
        {
            graph[i].push_back(V);
            graph[V].push_back(i);
            capacity[i][V] = 1;
            cost[i][V] = cost[V][i] = 0.0;
        }

        for (int i = 1; i <= n; i++)
        {
            scanf("%lf %lf %lf", &X[i], &Y[i], &speed[i]);
        }

        for (int i = n + 1; i <= n + m; i++)
        {
            scanf("%lf %lf", &X[i], &Y[i]);
            int current;

            while (scanf("%d", &current) && current)
            {
                graph[i].push_back(current);
                graph[current].push_back(i);
                cost[current][i] =
                    hypot(X[i] - X[current], Y[i] - Y[current]) / speed[current];
                cost[i][current] = -cost[current][i];
                capacity[current][i] = 1;
            }
        }

        printf("%.1lf\n", EdmondKarp());
    }

    return 0;
}

#include <bits/stdc++.h>
#define INF INT_MAX
#define MAX_NODES 4010
#define MAX_CHAR 256

using namespace std;

typedef pair<int, int> PairInt;
typedef pair<int, string> PairIntString;
typedef pair<PairInt, string> PairIntIntString;

int numNodes, distances[MAX_NODES], isVisited = 1;
int visited[MAX_NODES][MAX_CHAR];
vector<list<PairIntString>> adjacencyList(MAX_NODES);
unordered_map<string, int> nodesMapping;
pair<unordered_map<string, int>::iterator, bool> result;

int dijkstraAlgorithm(int startNode, int endNode, list<PairIntString>::iterator current)
{
    if (!adjacencyList[startNode].size())
        return INF;
    for (int i = 0; i < nodesMapping.size(); ++i)
        distances[i] = INF;
    visited[startNode][current->second[0]] = isVisited;
    priority_queue<PairIntIntString> queue;
    queue.push(make_pair(make_pair(-current->second.size(), current->first), current->second));

    list<PairIntString>::iterator iter, iter2;

    while (!queue.empty()) {
        PairIntIntString current = queue.top();
        queue.pop();
        int cost = -current.first.first;
        int v = current.first.second;
        if (v == endNode)
            return cost;
        if (visited[v][current.second[0]] == isVisited)
            continue;
        visited[v][current.second[0]] = isVisited;
        int previous = -1;
        for (iter = adjacencyList[v].begin(); iter != adjacencyList[v].end(); ++iter) {
            if (current.second[0] == iter->second[0])
                continue;
            if (distances[iter->first] > cost + int(iter->second.size())) {
                distances[iter->first] = cost + int(iter->second.size());
                queue.push(make_pair(make_pair(-distances[iter->first], iter->first), iter->second));
            } else if (previous == iter->first)
                queue.push(make_pair(make_pair(-(cost + int(iter->second.size())), iter->first), iter->second));
            previous = iter->first;
        }
    }
    return INF;
}

int main()
{
    ios::sync_with_stdio(false);
    int nodeFrom, nodeTo;
    string from, to, cost, source, destination;
    while (cin >> numNodes && numNodes) {
        int t = 0;
        nodesMapping.clear();
        cin >> source >> destination;
        nodesMapping.insert(make_pair(source, t++));
        nodesMapping.insert(make_pair(destination, t++));
        for (int i = 0; i < numNodes; ++i) {
            cin >> from >> to >> cost;
            result = nodesMapping.insert(make_pair(from, t));
            if (!result.second)
                nodeFrom = nodesMapping[from];
            else {
                nodeFrom = nodesMapping[from];
                t++;
            }
            result = nodesMapping.insert(make_pair(to, t));
            if (!result.second)
                nodeTo = nodesMapping[to];
            else {
                nodeTo = nodesMapping[to];
                t++;
            }
            adjacencyList[nodeFrom].push_back(make_pair(nodeTo, cost));
            adjacencyList[nodeTo].push_back(make_pair(nodeFrom, cost));
        }
        list<PairIntString>::iterator iter;
        int response = INF;
        for (iter = adjacencyList[0].begin(); iter != adjacencyList[0].end(); ++iter) {
            response = min(response, dijkstraAlgorithm(0, 1, iter));
            isVisited++;
        }
        if (response < INF)
            cout << response << "\n";
        else
            cout << "impossivel\n";
        for (int i = 0; i < t; ++i)
            adjacencyList[i].clear();
    }
    return 0;
}

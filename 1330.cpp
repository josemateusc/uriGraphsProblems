#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// Define constants.
const int directionX[] = {-1, 0, 1, 0}; // Used for X direction movement.
const int directionY[] = {0, 1, 0, -1}; // Used for Y direction movement.
const int MAX_ROWS = 100;
const int MAX_COLS = 100;
const int MAX_NODES = MAX_ROWS * MAX_COLS;

int numRows, numCols, numStones;
bool lakeMatrix[MAX_ROWS][MAX_COLS]; // Lake matrix.
bool visitedNodes[MAX_NODES];     // Marks visited nodes.
int nodePairs[MAX_NODES];        // Stores pairs.
vector<int> adjacencyNodes[MAX_NODES]; // Adjacency nodes list.

// Tries to augment a path in the graph.
bool tryPathAugmentation(int node) {
    if (visitedNodes[node]) return false;
    visitedNodes[node] = true;

    for (int adjacentNode : adjacencyNodes[node]) {
        if (nodePairs[adjacentNode] == -1 || tryPathAugmentation(nodePairs[adjacentNode])) {
            nodePairs[adjacentNode] = node;
            return true;
        }
    }

    return false;
}

// Calculates maximum matching in bipartite graph.
int calculateMaxMatching() {
    memset(nodePairs, -1, sizeof(nodePairs));
    int maxMatches = 0;

    for (int node = 0; node < numRows * numCols; node++) {
        memset(visitedNodes, false, sizeof(visitedNodes));
        if (tryPathAugmentation(node)) {
            maxMatches++;
        }
    }

    return maxMatches;
}

// Validates if a coordinate (x, y) is valid.
bool isCoordinateWithinBounds(int x, int y) {
    return (x >= 0 && x < numRows && y >= 0 && y < numCols);
}

int main() {
    while (cin >> numRows >> numCols && numRows != 0 && numCols != 0) {
        cin >> numStones;
        memset(lakeMatrix, false, sizeof(lakeMatrix));

        // Read stone positions.
        for (int i = 0; i < numStones; i++) {
            int x, y;
            cin >> x >> y;
            lakeMatrix[x - 1][y - 1] = true;
        }

        // Clear adjacency lists.
        for (int i = 0; i < numRows * numCols; i++) {
            adjacencyNodes[i].clear();
        }

        // Create the bipartite graph.
        int emptyLandCount = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (!lakeMatrix[i][j]) {
                    emptyLandCount++;

                    for (int k = 0; k < 4; k++) {
                        int nextX = i + directionX[k];
                        int nextY = j + directionY[k];

                        if (isCoordinateWithinBounds(nextX, nextY) && !lakeMatrix[nextX][nextY]) {
                            int node = i * numCols + j;
                            int adjacentNode = nextX * numCols + nextY;
                            adjacencyNodes[node].push_back(adjacentNode);
                        }
                    }
                }
            }
        }

        // Calculate the maximum matching.
        int maxProperties = calculateMaxMatching();
        int maxSold = maxProperties / 2;
        cout << maxSold << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> matrix(N);
    vector<int> houses(N, -1);
    int house_id = 0;

    for (int i = 0; i < N; ++i) {
        cin >> matrix[i];
    }

    for (int i = 0; i < N; ++i) {
        if (houses[i] == -1) {
            houses[i] = house_id;
            for (int j = i + 1; j < N; ++j) {
                if (matrix[i][j] == 'S') {
                    houses[j] = house_id;
                }
            }
            ++house_id;
        }
    }

    bool consistent = true;
    for (int i = 0; i < N && consistent; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (matrix[i][j] != (houses[i] == houses[j] ? 'S' : 'D')) {
                consistent = false;
                break;
            }
        }
    }

    if (!consistent) {
        cout << -1 << endl;
    } else {
        vector<int> house_sizes(house_id, 0);
        for (int house : houses) {
            ++house_sizes[house];
        }
        sort(house_sizes.rbegin(), house_sizes.rend());

        cout << house_id << endl;
        for (int i = 0; i < house_id; ++i) {
            cout << house_sizes[i] << (i + 1 < house_id ? ' ' : '\n');
        }
    }

    return 0;
}

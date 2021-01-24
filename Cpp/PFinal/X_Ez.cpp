#include <iostream>
#include <queue>
using namespace std;

void printMap(int *, int);
int minDadu(int *, int);
int min(int, int);

int main(void) {
    int V, t, c, a, b;
    cin >> V; // Jumlah petak
    cin >> t; // Banyak testcase
    int *map = new int[V];

    while (t-- > 0) {
        
        // Make map
        for (int i = 0; i < V; i++) {
            map[i] = -1;
        }

        cin >> c; // Banyak ular & tangga
        while (c-- > 0) {
            cin >> a >> b;
            map[a] = b;
        }
        // printMap(map, V);

        int count = minDadu(map, V);
        if (count == -1) return 1;
        cout << count << endl;
    }
    delete[] map;
    return 0;
}

int minDadu(int *map, int V) {
    bool *vis = new bool[V];
    for (int i = 0; i < V; i++) {
        vis[i] = false;
    }
    queue<int> q;
    int targetIdx = V - 1;
    int steps = 0;

    // At node 0
    vis[0] = true;
    int start = 0; // vertex
    q.push(start);

    while (!q.empty()) {
        int size = q.size();
        while (size-- > 0) {

            // Dequeue front
            int nowIdx = q.front();
            q.pop();

            if (nowIdx == targetIdx) return steps;
            int limit = min(targetIdx, nowIdx + 6);
            for (int nextIdx = nowIdx + 1; nextIdx <= limit; nextIdx++) {

                // Check if nextIdx is a snake/ladder
                int dest = (map[nextIdx] == -1)? nextIdx : map[nextIdx] - 1;
                if (vis[dest]) continue;

                // Queue nextIdx
                q.push(dest);
                vis[dest] = true;
            }
        }
        steps++;
    }
    delete[] vis;
    return -1;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

void printMap(int *map, int V) {
    cout << "\nMAP" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " = " << map[i] << endl;
    }
}
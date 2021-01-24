/* Longest Path (DFSMod)
https://www.hackerrank.com/contests/sdd-m45/challenges/jarak-terjauh
*/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Graph
{
    private:
        int V;
        vector<int> *adjList;
        void DFSUtil(int, int, int*, bool*);

    public:
        Graph(int);
        ~Graph();

        void addEdge(int, int);
        int longestPath();
};

int main()
{
    int V;
    cin >> V;

    Graph graph(V); // Construct graph

    int V1, V2;
    for (int i = 0; i <  V - 1; i++) {
        cin >> V1 >> V2;
        graph.addEdge(V1, V2); // Insert edge to adjList
    }

    int max = graph.longestPath();
    cout << max << endl;

    return 0;
}

Graph::Graph(int V)
{
    this->V = V;
    adjList = new vector<int>[V];
}

Graph::~Graph()
{
    adjList->clear();
}

void Graph::addEdge(int V1, int V2)
{
    adjList[V1 - 1].push_back(V2 - 1);
    adjList[V2 - 1].push_back(V1 - 1);
}

int Graph::longestPath()
{
    int max = -1;
    bool *visited = new bool[V];

    // DFS for each vertex
    for (int i = 0; i < V; i++) {
        memset(visited, false, sizeof(bool) * V);
        DFSUtil(i, 0, &max, visited);
    }

    delete[] visited;
    return max;
}

void Graph::DFSUtil(int curr, int prev_len, int *max, bool *visited)
{
    visited[curr] = true;
    int curr_len = 0;

    // Traverse every adjacent vertex
    for (int adjacent : adjList[curr]) {
        if (!visited[adjacent]) {
            curr_len = prev_len + 1;

            // DPS for each adjacent
            DFSUtil(adjacent, curr_len, max, visited);
        }

        if ((*max) < curr_len) {
            *max = curr_len;
        }
        curr_len = 0;
    }
}
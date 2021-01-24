#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
#include <list>
using namespace std;

// pii pair of integer, integer
typedef pair<int, int> pii;

class Graph
{
    private:
        int V, E;
        vector<pii> *adjList; // weighted
        int *dist;
        bool *vis;

        void DFS(int, int);

    public:
        Graph(int, int); // Construct ajdList & edgeList
        ~Graph();

        // Undirected Graph, Start from index 1
        void Add_adjList(int, int, int);
        void Jalan(int, int); // src, L
};

void printArr(int *, int);

int main()
{
    int V, E;
    cin >> V;
    cin >> E;

    Graph graph(V, E);
    int V1, V2, W, X, L;

    for (int i = 0; i < E; i++) {
        cin >> V1 >> V2 >> W;
        graph.Add_adjList(V1, V2, W);
    }
    cin >> X >> L;

    // Add limiter (L)
    graph.Jalan(X, L);

    return 0;
}

Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    adjList = new vector<pii>[V];
}

Graph::~Graph() 
{
    adjList->clear();
}

void Graph::Add_adjList(int V1, int V2, int W)
{
    // Vertex, Weight
    adjList[V1].push_back(make_pair(V2, W));
}

void Graph::DFS(int curr, int L)
{
    vis[curr] = true;
    if (L == 0) return;

    // Traverse every adjacent vertices
    for (pii adj : adjList[curr]) {
        int newDist = dist[curr] + adj.second;

        if (vis[adj.first] && newDist >= dist[adj.first]) continue;

        if (newDist < dist[adj.first]) { 
            dist[adj.first] = newDist;
        }
        
        DFS(adj.first, L - 1);
    }
}

void Graph::Jalan(int start, int batas)
{
    dist = new int[V];
    vis = new bool[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        vis[i] = false;
    }
    dist[start] = 0;
    DFS(start, batas);

    for (int i = 0; i < V; i++) {
        cout << i << " ";

        if (dist[i] == INT_MAX)
            cout << "INFINITY" << endl;
        else
            cout << dist[i] << endl;
    }
}

void printArr (int *dist, int V)
{
    for (int i = 0; i < V; i++) {
        cout << i << " ";

        if (dist[i] == INT_MAX) {
            cout << "INFINITY" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
}
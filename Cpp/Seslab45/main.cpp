#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

class Graph
{
    private:
        int V, E;
        vector<pii> *adjList; // weighted
        vector<pair<pii, int> > *edgeList; // weighted

        void DFSUtil(int, bool*);
        void find(int);

    public:
        Graph(int, int); // Construct ajdList & edgeList
        ~Graph();

        // Undirected Graph, Start from index 1
        void Add_adjList(int, int, int);
        void Add_edgeList(int, int, int);

        void DFS(int);
        void BFS(int);
        void Djikstra(int);
        // void Kruskal(); // return minimal weight
};

int main()
{
    int V, E;
    cin >> V >> E;

    Graph graph(V, E); // Construct graph

    int V1, V2, W;
    for (int i = 0; i <  V - 1; i++) {
        cin >> V1 >> V2 >> W;
        graph.add_adjList(V1, V2, W); // Insert edge to adjList
    }

    return 0;
}

Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    adjList = new vector<pii>[V];
    edgeList = new vector<pair<pii, int> >[E];
}

Graph::~Graph()
{
    adjList->clear();
    edgeList->clear();
}

void Graph::Add_adjList(int V1, int V2, int W)
{
    // Vertex, Weight
    adjList[V1 - 1].push_back(make_pair(V2 - 1, W));
    adjList[V2 - 1].push_back(make_pair(V1 - 1, W));
}

void Graph::Add_edgeList(int V1, int V2, int W)
{
    // Source, Destination, Weight
    edgeList->push_back(make_pair(make_pair(V1 - 1, V2 - 1), W));
    edgeList->push_back(make_pair(make_pair(V2 - 1, V1 - 1), W));
}

void Graph::BFS(int start)
{
    bool *vis = new bool[V];
    memset(vis, false, sizeof(bool) * V);

    // Create queue
    list<int> queue;

    vis[start] = true;
    queue.push_back(start);

    while (!queue.empty()) {

        // Dequeue front and print it
        start = queue.front();
        cout << start << " ";;
        queue.pop_front();

        // Enqueue all unvisited, adjacent vertices
        for (pii adj : adjList[start]) {

            if (!vis[adj.first]) {
                vis[adj.first] = true;
                queue.push_back(adj.first);
            }
        }
    }
    delete[] vis;
    cout << endl;
}

void Graph::DFS(int start)
{
    bool *vis = new bool[V];

    // DFS for each vertex
    memset(vis, false, sizeof(bool) * V);
    DFSUtil(start, vis);

    delete[] vis;
    cout << endl;
}

void Graph::DFSUtil(int curr, bool *vis)
{
    vis[curr] = true;
    cout << curr << " ";

    // Traverse every adjacent vertices
    for (pii adj : adjList[curr]) {
        if (!vis[adj.first]) {

            // DPS for each adjacent vertex
            DFSUtil(adj.first, vis);
        }
    }
}

void Graph::Djikstra(int start)
{
    bool vis[V];
    int dist[V];
    memset(vis, false, sizeof(bool) * V);
    memset(dist, -1, sizeof(int) * V);

    priority_queue <pii, vector <pii>, greater <pii> > pq;
    pq.push(make_pair(0, start)); // Format: distance, vertex
    dist[start] = 0;

    while(!pq.empty()) {
        // Get current vertex index and weight
        int nowVertex = pq.top().second;
        int nowCost = pq.top().first;
        pq.pop();

        vis[nowVertex] = true;

        if (nowCost > dist[nowVertex]) continue;

        // Traverse every unvisited, adjacent vertices
        for (pii next : adjList[nowVertex]) {

            // Get next vertex index and weight
            int nextVertex = next.first;
            int nextCost = next.second; // cost

            if (vis[nextVertex]) continue;
            int newDist = dist[nowVertex] + nextCost;

            // If shorter route is found or route lenght is infinity (unconnected)
            if (newDist < dist[nextVertex] || dist[nextVertex] == -1) {
                dist[nextVertex] = newDist;
                pq.push(make_pair(dist[nextVertex], nextVertex));
            }
        }
    }

    for (int i = 0; i < V; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
}

// void Graph::Kruskal()
// {
//     vector<pair<pii, int> > result;
//     vector<pii> par; // Format: parent, id

//     for (int i = 0; i < V; i++) {
//         par[i].first = i; // parent
//         par[i].second = 0; // id
//     }

//     int r = 0; // Index for result[]
//     int e = 0; // Index for sorted edges

//     while (r < V - 1 && e < E) {

//         auto nextEdge = edgeList[e++];

//         int x = find(par, nextEdge.first - 1);
//         int y = find(subsets, nextEdge.dest - 1);

//         if (x != y) {
//             result[r++] = nextEdge;
//             Union(subsets, x, y);
//         }
//     }
//     // cout << "Following are the edges in the constructed MST" << endl;  
//     // for (int i = 0; i < r; i++) {
//     //     cout << result[i].src << " -- " << result[i].dest << endl;  
//     // }
//     return;
// }
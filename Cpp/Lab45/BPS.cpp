// https://www.hackerrank.com/contests/sdd-m45/challenges

#include <iostream>
#include <list>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;

    public:
        Graph(int V);
        void addEdge(int v, int w);
        void BFS(int s);
};

int main(void) {
    int V, E;
    cin >> V;
    cin >> E;

    Graph g(V); // Construct graph

    int V1, V2, X;
    for (int i = 0; i < E; i++) {
        cin >> V1 >> V2;
        g.addEdge(V1, V2); // Insert to adjList
    }
    cin >> X;

    g.BFS(X);
    return 0;
}

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::BFS(int s)
{
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    list<int> queue;

    visited[s] = true;
    queue.push_back(s);

    list<int>::iterator i;

    while(!queue.empty())
    {
        s = queue.front();
        cout << s << " -> ";
        queue.pop_front();

        // Traverse every adjacent vertex
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    cout << "END" << endl;
}
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <algorithm> // Include this header for the std::reverse function

using namespace std;

typedef pair<int, int> Pair; // Pair represents the vertex number and the distance to that vertex

class Graph {
    int V; 
    list<Pair> *adj; 
public:
    Graph(int V); // Constructor
    void addEdge(int u, int v, int w); 
    void shortestPath(int s, int t); 
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<Pair>[V];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); // This line makes the graph undirected, remove it if the graph is directed
}

void Graph::shortestPath(int src, int target) {
    vector<int> dist(V, numeric_limits<int>::max()); // Distance values initialized to infinity
    vector<bool> visited(V, false); // Visited array initialized to false
    vector<int> prev(V, -1); // To store the path

    priority_queue<Pair, vector<Pair>, greater<Pair>> pq; 
    dist[src] = 0; // Distance from the source to itself is always 0
    pq.push(make_pair(0, src)); // Push the source with distance 0

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue; // If u has already been visited, skip processing
        visited[u] = true; // Mark this node as visited

        for (auto i : adj[u]) {
            int v = i.first;
            int weight = i.second;

            // Only consider this vertex if it has not been visited
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    vector<int> path;
    for (int at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Output the results
    if (dist[target] != numeric_limits<int>::max()) {
        cout << "Path cost from " << src << " to " << target << ": " << dist[target] << endl;
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i < path.size() - 1 ? " -> " : "");
        }
        cout << endl;
    } else {
        cout << "No path exists from " << src << " to " << target << endl;
    }
}

int main() {
    int V = 5; // since we are using 5 vertices
    Graph g(V);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 3, 9);
    g.addEdge(3, 2, 7);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 3, 8);
    g.addEdge(4, 1, 4);

    int source, target;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter target vertex: ";
    cin >> target;
    g.shortestPath(source, target);

    return 0;
}
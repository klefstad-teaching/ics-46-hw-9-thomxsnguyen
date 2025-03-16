#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

struct Node {
    int vertex;
    int weight;
    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);  

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distances[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distances[v]));
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    if (distances[destination] == INF) {
        return {};  
    }

    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found" << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) cout << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}

#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

int main() {
    string filename;
    cout << "Enter graph file name: ";
    cin >> filename;

    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    for (int u = 0; u < G.numVertices; ++u) {
        int originalSize = G[u].size();
        for (int i = 0; i < originalSize; ++i) {
            Edge e = G[u][i];
            bool found = false;
            for (const Edge& rev : G[e.dst]) {
                if (rev.dst == u && rev.weight == e.weight) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                G[e.dst].push_back(Edge(e.dst, u, e.weight));
            }
        }
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}

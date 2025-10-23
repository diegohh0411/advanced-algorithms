// A01198786, Diego Hernández Herrera

#include <iostream>
#include <vector>
#include <list>

struct Edge {
    int v; // To vertex
    int flow; // Current flow in edge
    int capacity; // Max amount of flow
    int reverse; // The index of the revers edge in the Adjacent Array
};

class Graph {
    int n; // Amount of nodes
    int* level; // Array of ints, stores the level of the nodes in the graph. Each node has a "level".
    std::vector<Edge>* adj; // An array of Edges

public:
    Graph(int n) {
        adj = new std::vector<Edge>[n];
        this->n = n;
        level = new int[n];
    }

    void addEdge(int u, int v, int c) {
        std::cout << "Adding edge <" << u << " --" << c << "-- " << v << ">" << std::endl; 

        // Forward edge
        Edge a { v, 0, c, (int)adj[v].size() };

        // Backward edge
        Edge b { u, 0, 0, (int)adj[u].size()};

        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    // This DFS-based function finds out if more flow can be sent from node S to node T
    bool isFlowPossible(int s, int t) { // Source (s) and Sink (t)
        for (int i = 0; i < n; i++)
            level[i] = -1;

        level[s] = 0; // Level of the source node is always 0

        std::list<int> q;
        q.push_back(s);

        std::vector<Edge>::iterator i;

        while (!q.empty()) {
            int u = q.front();
            q.pop_front();

            for (i = adj[u].begin(); i != adj[u].end(); i++) {
                Edge& e = *i;

                if (level[e.v] < 0 && e.flow < e.capacity) {
                    level[e.v] = level[u] + 1;

                    q.push_back(e.v);
                }
            }
        }

        return level[t] < 0 ? false : true;
    }

    // This DFS-based function sends flow after Graph::DFS has figured out if there is more possible flow.
    int sendFlow(int u, int flow, int t, int start[]) {
        if (u == t) // Sink has been reached
            return flow;

        // Traverse all adjacent edges
        for (; start[u] < adj[u].size(); start[u]++) {
            Edge& e = adj[u][start[u]];

            if (level[e.v] == level[u] + 1 && e.flow < e.capacity) { // If the next node has one more level than current node and its capacity hasn't overflowed
                int current_flow = std::min(flow, e.capacity - e.flow);

                int temp_flow = sendFlow(e.v, current_flow, t, start);

                if (temp_flow > 0) {
                    e.flow += temp_flow;

                    adj[e.v][e.reverse].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }

        return 0;
    }

    int maxFlow(int s, int t) {
        if (s == t) 
            return -1;

        int total = 0;

        while (isFlowPossible(s, t) == true) { // Augment the flow while there's still a path from source to sink
            int* start = new int[n + 1] { 0 }; // Stores how many edges are visited

            while (int flow = sendFlow(s, INT_MAX, t, start)) {
                total += flow;
            }

            delete[] start;             
        }

        return total;
    }
};

int main() {
    int n, e, u, v, c;
    std::cin >> n >> e;

    Graph g(n + 1); // +1 to accommodate 1-indexed nodes

    for (int i = 0; i < e; i++) {
        std::cin >> u >> v >> c;
        g.addEdge(u, v, c);
    }

    std::cout << g.maxFlow(1, n);
        
    return 0;
}
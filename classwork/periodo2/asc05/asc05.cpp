// Diego Hernández Herrera, A0119878

#include <iostream>
#include <vector>
#include <climits>
#include <tuple>
#include <algorithm>

#define INF INT_MAX

using Mat = std::vector<std::vector<int>>;
using NodeCost = std::tuple<int, int>; // The destination node and its cost

// Complejidad: O(n²) donde n es la cantidad de vértices
void print(Mat& m) {
    int n = m.size();

    for (int i = 0; i < n; i++) {
        std::cout << "[";

        for (int j = 0; j < n; j++) {
            int content = m[i][j];

            if (content == INF) {
                std::cout << "INF\t";
            } else {
                std::cout << m[i][j] << "\t";
            }
        }

        std::cout << "]" << std::endl;
    }
}

// Complejidad: O(n³) donde n es la cantidad de vértices
void floydWarshall (Mat& mat) {
    int v = mat.size();

    // Initialize diagonal to 0
    for (int i = 1; i < v; i++) {
        mat[i][i] = 0;
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (
                    mat[i][k] != INF &&
                    mat[k][j] != INF &&
                    mat[i][j] > mat[i][k] + mat[k][j]
                ) {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
}

// Complejidad: O(n³) por la llamada a la función floydWarshall
void calculateFloyd(Mat& mat, int source) {
    Mat copy = mat;
    int v = mat.size();
    floydWarshall(copy);

    for (int i = 1; i < v; i++) {
        if (i != source) {
            std::cout << source << " --> " << i << ": " << copy[source][i] << std::endl;
        }
    }
}

// Complejidad: O(n²) donde n es la cantidad de vértices
int dijkstra(Mat& mat, int source, int destination) {
    int v = mat.size();
    std::vector<int> distances(v, INF); 
    std::vector<int> visited(v, false);
    distances[source] = 0;

    while (true) {
        int current_node = -1;
        int min_dist = INF;

        for (int i = 1; i < v; i++) {
            if (!visited[i] && distances[i] < min_dist) {
                min_dist = distances[i];
                min_dist = distances[i];
                current_node = i;
            }
        }

        if (current_node == -1 || current_node == destination) break;

        visited[current_node] = true;

        for (int neighbor = 1; neighbor < v; neighbor++) {
            if (
                mat[current_node][neighbor] != INF &&
                !visited[neighbor]
            ) {
                int new_dist = distances[current_node] + mat[current_node][neighbor];

                if (new_dist < distances[neighbor]) {
                    distances[neighbor] = new_dist;
                }
            }
        }
    }

    return distances[destination];
}

// Complejidad: O(n³) porque se llama al algoritmo de dijkstra (n²) otras n veces, n * n² = n³
void calculateDijkstras(Mat& mat, int source) {
    int m = mat.size();

    std::cout << "Dijkstra:" << std::endl;
    for (int i = 1; i < m; i++) {
        if (i == source) {
            continue;
        }

        int cost = dijkstra(mat, source, i);

        std::cout << source << " --> " << i << ": " << cost << std::endl;
    }
}

// Complejidad: O(n³) por los cálculos de Dijkstra y Floyd-Warshall
int main() {
    int v, e, s; // `v` represents the number of vertices, `e` the number of edges and `s` the source

    std::cin >> v >> e >> s;

    std::vector<std::vector<int>> adj;
    adj.resize(v + 1, std::vector<int>(v + 1, INF));

    for (int i = 0; i < e; i++) {
        int f, t, c;
        std::cin >> f >> t >> c;

        adj[f][t] = c;
        adj[t][f] = c;
    }

    calculateFloyd(adj, s);
    calculateDijkstras(adj, s);

    return 0;
}
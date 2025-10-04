// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

using Matrix = std::vector<std::vector<int>>;

// Complejidad: O(n^2), donde n es el número de nodos
void print(Matrix& m) {
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

// Complejidad: O(n^2) donde n es la cantidad de vértices
int dijkstra(Matrix& mat, int source, int destination) {
    int nodes = mat.size();
    std::vector<int> distances(nodes, INF); 
    std::vector<int> visited(nodes, false);
    distances[source] = 0;

    while (true) {
        int current_node = -1;
        int min_dist = INF;

        for (int i = 1; i < nodes; i++) {
            if (!visited[i] && distances[i] < min_dist) {
                min_dist = distances[i];
                current_node = i;
            }
        }

        if (current_node == -1 || current_node == destination) break;

        visited[current_node] = true;

        for (int neighbor = 1; neighbor < nodes; neighbor++) {
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

// Complejidad: O(n^3) donde n es la cantidad de vértices (ejecuta Dijkstra n veces)
std::vector<int> calculateShortestPaths(Matrix& m) {
    int nodes = m.size();

    std::vector<int> shortestPaths;

    for (int i = 0; i < nodes; i++) {
        int cost = dijkstra(m, 1, i);

        shortestPaths.push_back(
            cost == INF ? -1 : cost
        );
    }

    return shortestPaths;
}


// Complejidad: O(n^2 + m), donde n es el número de nodos y m es el número de aristas
Matrix buildAdjacencyMatrix(int nodes, int edges) {
    Matrix matr;
    matr.resize(nodes + 1, std::vector<int>(nodes + 1, INF));

    char source, destination;
    int cost;

    for (int i = 0; i < edges; i++) {
        std::cin >> source >> destination >> cost;

        int source_int = source - 'A' + 1;
        int destination_int = destination - 'A' + 1;

        matr[source_int][destination_int] = cost;
        matr[destination_int][source_int] = cost;
    }

    return matr;
}

// Complejidad: O(k * n^3) donde k es el número de casos y n es la cantidad de vértices
int main() {
    int no_of_cases;
    std::cin >> no_of_cases;

    for (int case_no = 0; case_no < no_of_cases; case_no++) {
        int nodes, edges;

        std::cin >> nodes >> edges;

        Matrix m = buildAdjacencyMatrix(nodes, edges);

        std::vector<int> shortestPaths = calculateShortestPaths(m);

        int longestShortestPath = -1;
        int longestNode = -1;

        // Complejidad: O(n) donde n es la cantidad de nodos
        for (int i = 1; i <= nodes; i++) {
            if (
                shortestPaths[i] != -1 &&
                shortestPaths[i] > longestShortestPath
            ) {
                longestShortestPath = shortestPaths[i];
                longestNode= i;
            }
        }

        char node_letter = 'A' - 1 + longestNode;
        std::cout << "Case " << (case_no + 1) << ": " << node_letter << std::endl;
    }

    return 0;
}
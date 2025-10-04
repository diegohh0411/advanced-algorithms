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

// Complejidad: O(n^2), donde n es el número de nodos (vértices). Este es el costo del algoritmo de Dijkstra usando una matriz de adyacencia.
int modifiedDijkstra(Matrix& noise, int source, int destination) {
    int n = noise.size();
    std::vector<int> max_noise_in_route(n, INF); 
    std::vector<int> visited(n, false);
    max_noise_in_route[source] = 0;

    while (true) {
        int current_node = -1;
        int min_noise = INF;

        for (int i = 1; i < n; i++) {
            if (
                !visited[i] 
                && max_noise_in_route[i] < min_noise
            ) {
                min_noise = max_noise_in_route[i];
                current_node = i;
            }
        }

        if (current_node == -1 || current_node == destination) break;

        visited[current_node] = true;

        for (int neighbor = 1; neighbor < n; neighbor++) {
            if (
                noise[current_node][neighbor] != INF &&
                !visited[neighbor]
            ) {
                int new_max_noise = std::max(max_noise_in_route[current_node], noise[current_node][neighbor]);

                if (new_max_noise < max_noise_in_route[neighbor]) {
                    max_noise_in_route[neighbor] = new_max_noise;
                }
            }
        }
    }

    return max_noise_in_route[destination];
}

// Complejidad: O(n^2 + m), donde n es el número de nodos y m es el número de aristas
Matrix buildAdjacencyMatrix(int nodes, int edges) {
    Matrix matr;
    matr.resize(nodes + 1, std::vector<int>(nodes + 1, INF));

    int c1, c2, d;

    for (int i = 0; i < edges; i++) {
        
        std::cin >> c1 >> c2 >> d;

        matr[c1][c2] = d;
        matr[c2][c1] = d;
    }

    return matr;
}

// Complejidad: O(T * (C^2 + S + Q * C^2)), donde T es el número de casos, C es el número de ciudades (nodos), S el número de calles (aristas) y Q el número de consultas. Por cada caso, se construye una matriz (C^2 + S) y luego por cada consulta se ejecuta Dijkstra modificado (C^2).
int main() {
    int no_of_cases;

    std::cin >> no_of_cases;

    for (int no = 0; no < no_of_cases; no++) {
        std::cout << "Case " << (no + 1) << ":" << std::endl;

        int c, s, no_of_queries;
        std::cin >> c >> s >> no_of_queries;

        Matrix m = buildAdjacencyMatrix(c, s);

        for (int q = 0; q < no_of_queries; q++) {
            int c1, c2;
            std::cin >> c1 >> c2;

            int noise = modifiedDijkstra(m, c1, c2);

            if (noise == INF)
                std::cout << "no path"  << std::endl;
            else
                std::cout << noise << std::endl;
        }
    }

    return 0;
}
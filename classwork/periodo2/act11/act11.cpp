// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

using adjMatrix = std::vector<std::vector<int>>;

// Complejidad: O(1)
int charToInt(char x) {
    int i = x - 'A';
    return i;
}

// Complejidad: O(1)
char intToChar(int x) {
    char c = 'A' + x;
    return c;
}

// Complejidad: O(2^n * n^2)
int heldKarp(adjMatrix& graph) {
    int n = graph.size();
    
    // dp[mask][i] = minimum cost to visit all nodes in mask ending at node i
    std::vector<std::vector<int>> dp(1 << n, std::vector<int>(n, INF));
    
    // Start at node 0, which is the house A
    dp[1][0] = 0;
    
    // Iterate through all subsets
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int last = 0; last < n; last++) {
            // Skip if last node is not in the current subset
            if (!(mask & (1 << last))) {
                continue;
            }
            
            // Skip if we haven't reached this state yet
            if (dp[mask][last] == INF) {
                continue;
            }
            
            // Try to extend to next node
            for (int next = 0; next < n; next++) {
                // Skip if next is already visited
                if (mask & (1 << next)) {
                    continue;
                }
                
                // Skip if there's no edge
                if (graph[last][next] == INF) {
                    continue;
                }
                
                int newMask = mask | (1 << next);
                int newCost = dp[mask][last] + graph[last][next];
                
                if (newCost < dp[newMask][next]) {
                    dp[newMask][next] = newCost;
                }
            }
        }
    }
    
    // Find minimum cost to visit all nodes and return to start
    int fullMask = (1 << n) - 1;
    int minCost = INF;
    
    for (int last = 0; last < n; last++) {
        if (dp[fullMask][last] == INF) {
            continue;
        }
        
        if (graph[last][0] == INF) {
            continue;
        }
        
        int totalCost = dp[fullMask][last] + graph[last][0];
        
        if (totalCost < minCost) {
            minCost = totalCost;
        }
    }
    
    return minCost;
}

// Complejidad temporal: O(N^2 + M)
adjMatrix readInput() {    
    int N, M;
    std::cin >> N >> M;
    
    adjMatrix graph(N, std::vector<int>(N, INF));
    
    for (int i = 0; i < N; i++) {
        graph[i][i] = 0;
    }
    
    for (int i = 0; i < M; i++) {
        char origin, destination;
        int cost;
        
        std::cin >> origin >> destination >> cost;
        
        int i_origin = charToInt(origin);
        int i_destination = charToInt(destination);
        
        graph[i_origin][i_destination] = cost;
        graph[i_destination][i_origin] = cost;
    }
    
    return graph;
}

int main() {
    adjMatrix graph = readInput();
    
    int result = heldKarp(graph);
    
    if (result == INF) {
        std::cout << "INF" << std::endl;
    } else {
        std::cout << result << std::endl;
    }
    
    return 0;
}
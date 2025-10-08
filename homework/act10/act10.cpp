// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <utility>

using PriceWeight = std::pair<int, int>; // <price, weight>
using ItemList = std::vector<PriceWeight>;

// Complejidad temporal: O(n * max_capacity), donde n es el número de items
// Retorna un vector con el valor máximo para cada capacidad de 0 a max_capacity
std::vector<int> knapsack(ItemList& items, int max_capacity) {
    int n = items.size();

    // dp[i][w] = max value using first i items with weight limit w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max_capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        int price = items[i - 1].first;
        int weight = items[i - 1].second;

        for (int w = 0; w <= max_capacity; w++) {
            // Don't take the item i
            dp[i][w] = dp[i - 1][w];

            // Take item i (if it fits) 
            if (weight <= w) {
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weight] + price);
            }
        }
    }

    // Retornar la última fila (resultados para todas las capacidades)
    return dp[n];
}

// Complejidad temporal: O(t * (n + g + n * max_capacity)), donde max_capacity es el peso máximo entre todas las personas
int main() {
    int t, n, p, w, g, mw;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        std::cin >> n;

        ItemList items = {};

        for (int j = 0; j < n; j++) {
            std::cin >> p >> w;
            items.push_back(
                std::make_pair(p, w)
            );
        }

        std::cin >> g;

        // Leer todas las capacidades y encontrar la máxima
        std::vector<int> capacities;
        int max_capacity = 0;

        for (int j = 0; j < g; j++) {
            std::cin >> mw;
            capacities.push_back(mw);
            max_capacity = std::max(max_capacity, mw);
        }

        // Calcular knapsack una sola vez hasta la capacidad máxima
        std::vector<int> dp = knapsack(items, max_capacity);

        // Sumar los valores para cada capacidad
        int totalValue = 0;
        for (int capacity : capacities) {
            totalValue += dp[capacity];
        }

        std::cout << totalValue << std::endl;
    }
}
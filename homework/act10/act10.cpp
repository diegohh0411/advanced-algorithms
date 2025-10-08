// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <utility>

using PriceWeight = std::pair<int, int>; // <price, weight>
using ItemList = std::vector<PriceWeight>;

int knapsack(ItemList& items, int capacity) {
    int n = items.size();

    // dp[i][w] = max value using first i items with weight limit w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        int price = items[i - 1].first;
        int weight = items[i - 1].second;

        for (int w = 0; w <= capacity; w++) {
            // Don't take the item i
            dp[i][w] = dp[i - 1][w];

            // Take item i (if it fits) 
            if (weight <= w) {
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weight] + price);
            }
        }
    }

    return dp[n][capacity];
}

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

        int totalValue = 0;

        for (int j = 0; j < g; j++) {
            std::cin >> mw;
            totalValue += knapsack(items, mw);
        }

        std::cout << totalValue << std::endl;
    }
}
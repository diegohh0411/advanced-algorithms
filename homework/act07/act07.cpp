// Diego Hernández Herrera, A01198786

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int algorithm() {
    std::string a, b;
    std::cin >> a >> b;

    int n = a.size();
    int m = b.size();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    return dp[n][m];
}

int main() {
    int n;
    std::cin >> n;
    
    for (int i = 1; i <= n; i++) {
        int result = algorithm();
        std::cout << "Case " << i << ": " << result << std::endl;
    }
}
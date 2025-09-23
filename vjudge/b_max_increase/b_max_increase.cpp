// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>

// Complejidad temporal: O(n)
int algorithm(std::vector<int>& vec, int& n) {
    if (n == 0) return 0;

    int max_len = 1;
    int current_len = 1;

    for (int i = 1; i < n; i++) { // O(n)
        if (vec[i] > vec[i - 1]) {
            current_len++;
        } else {
            if (current_len > max_len) max_len = current_len;
            current_len = 1;
        }
    }
    if (current_len > max_len) max_len = current_len;

    return max_len;
}

// Complejidad temporal: O(n)
int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);

    for (int i = 0; i < n; i++) // O(n)
        std::cin >> vec[i];

    std::cout << algorithm(vec, n) << std::endl; // O(n)

    return 0;
}


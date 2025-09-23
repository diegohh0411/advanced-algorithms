// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Complejidad de Tiempo: O(n)
std::vector<int> algorithm(std::string& s) {
    int n = s.length();

    std::vector<int> pi(n); // Usaré el array Pi del algoritmo del algoritmo de KMP.

    for (int i = 1; i < n; i++) { // O(n)
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            j++;
        }

        pi[i] = j;
    }

    std::vector<int> border_lengths;
    int k = pi[n - 1];
    while (k > 0) {
        border_lengths.push_back(k);
        k = pi[k - 1];
    }

    return border_lengths;
}

#include <algorithm>

// Complejidad temporal: O(n + n log n)
int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> border_lengths = algorithm(s); // O(n)
    std::sort(border_lengths.begin(), border_lengths.end()); // O(n log n)

    for (size_t i = 0; i < border_lengths.size(); ++i) {
        std::cout << border_lengths[i];
        if (i < border_lengths.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
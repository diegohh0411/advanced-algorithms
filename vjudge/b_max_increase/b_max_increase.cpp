// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>

int algorithm(std::vector<int>& vec, int& n) {
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int current_len = 1;
        int last_number = vec[i];

        for (int j = i + 1; j < n && vec[j] > last_number; j++) {
            current_len++;
            last_number = vec[j];
        }

        if (current_len > max_len) max_len = current_len;
    }

    return max_len;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);

    for (int i = 0; i < n; i++)
        std::cin >> vec[i];

    std::cout << algorithm(vec, n) << std::endl;

    return 0;
}


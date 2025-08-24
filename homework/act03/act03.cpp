// Diego Hernández Herrera, A01198786
// Escrito el domingo 24 de agosto

#include <iostream>
#include <vector>
#include <tuple>

// Complejidad temporal: O(n)
// Complejidad espacial: O(1)
std::tuple<int, int> calculateMaxDifference(std::vector<int>& nums) {
    int n = nums.size();

    int maxDifference = -1;
    std::tuple<int, int> indexes(-1, -1);

    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        int difference = nums[i] - nums[minIndex];

        if (difference > maxDifference) {
            maxDifference = difference;
            indexes = std::tuple<int, int>(minIndex, i);
        }

        if (nums[i] < nums[minIndex]) {
            minIndex = i;
        }
    }

    return indexes;
}

int main() {
    int n;
    std::cin >> n;

    // std::cout << "[Debug] { N : " << n << " }" << std::endl;

    for (int i = 0; i < n; i++) {
        int d;
        std::cin >> d;

        // std::cout << "[Debug] { D : " << d << " }" << std::endl;

        std::vector<int> nums;

        for (int j = 0; j < d; j++) {
            int t;
            std::cin >> t;
            nums.push_back(t);
            // std::cout << "[Debug] input was " << nums[j] << std::endl;
        }

        std::tuple<int, int> indexes = calculateMaxDifference(nums);
        std::cout << "Buy in " << std::get<0>(indexes) + 1 << ", sell in " << std::get<1>(indexes) + 1 << std::endl;
    }
}
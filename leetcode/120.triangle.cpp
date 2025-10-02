#include <bits/stdc++.h>
#include "leetcode.hpp"

class Solution {
public:
    int min(vector<int>& v, int& index) { // O(k)
        std::cout << "{ index: " << index << ", v.size: " << v.size() << " }" << std::endl;
        int idxa = index;
        int idxb = index + 1;
        if (idxb < v.size()) {
            int a = v[idxa];
            int b = v[idxb];

            if (a < b) {
                std::cout << "Chose <" << a << "> at index: " << idxa << std::endl;
                return idxa;
            }
            else {
                std::cout << "Chose <" << b << "> at index: " << idxb << std::endl;
                return idxb;
            };
        } else {
            return idxa;
        }
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        int sum = 0;
        int current_index = 0;
        for (int i = 0; i < n; i++) {      // O(n)
            current_index = this->min(triangle[i], current_index);
            sum += triangle[i][current_index];
        }

        return sum;
    }
};
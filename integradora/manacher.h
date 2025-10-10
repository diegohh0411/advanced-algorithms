#ifndef MANACHER_MANAGER
#define MANACHER_MANAGER

#include <string>
#include <vector>
#include <iostream>

using str = std::string;
using intVec = std::vector<int>;
using strPair = std::pair<str, str>;
using strPairVec = std::vector<strPair>;

str ManacherPreprocess(str& s) {
    str result = "#";

    for (char c : s) {
        result += c;
        result += "#";
    }

    return result;
}

std::tuple<int, int, str> Manacher(str s) { // <length, index, content>
    str T = ManacherPreprocess(s);
    int n = T.length();
    intVec P(n, 0);
    int C = 0;
    int R = 0;

    for (int i = 0; i < n; i++) {
        int mirror = 2 * C - i;

        if (i < R) {
            P[i] = std::min(R - i, P[mirror]);
        }

        int left = i - (P[i] + 1);
        int right = i + (P[i] + 1);

        while (left >= 0 && right < n && T[left] == T[right]) {
            P[i]++;
            left--;
            right++;
        }

        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }

    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 0; i < n; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    str palindrome = s.substr(start, maxLen);

    return std::make_tuple(
        maxLen,
        start,
        palindrome
    );
}

void ManacherManager(strPairVec& transmissions) {
    std::cout << "Palindromo mas grande:" << std::endl;

    for (strPair tr : transmissions) {
        auto [length, start, content] = Manacher(tr.second);

        std::cout << tr.first << " ==> Posicion: " << start << std::endl;
        std::cout << content << std::endl;
    }
}

#endif
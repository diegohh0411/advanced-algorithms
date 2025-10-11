#ifndef MANACHER_MANAGER
#define MANACHER_MANAGER

#include <string>
#include <vector>
#include <iostream>
#include "common.h"

// Complejidad: O(N), donde N es el tamaño del string.
str ManacherPreprocess(str& s) {
    str result = "#";

    for (char c : s) {
        result += c;
        result += "#";
    }

    return result;
}

// Complejidad: O(N), donde N es el tamaño del string.
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

// Complejidad: O(T * Q), donde T es el número de transmisiones y Q es la longitud de cada transmisión.
void ManacherManager(traVec& transmissions) {
    std::cout << "Palindromo mas grande:" << std::endl;

    for (Transmission tr : transmissions) {
        auto [length, start, content] = Manacher(tr.content);

        std::cout << tr.filename << " ==> Posicion: " << start << std::endl;
        std::cout << content << std::endl;
    }

    std::cout << "==============" << std::endl;
}

#endif
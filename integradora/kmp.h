#ifndef KMP_MANAGER
#define KMP_MANAGER

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "common.h"

using intVec = std::vector<int>;
using strVec = std::vector<str>;
using strPair = std::pair<str, str>;
using strPairVec = std::vector<strPair>;

intVec ComputeLps(str& pattern) {
    int m = pattern.length();
    intVec lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

intVec Kmp(str text, str pattern) {
    intVec positions;
    intVec lps = ComputeLps(pattern);

    int i = 0; // Índice para el texto
    int j = 0; // Índice para el patrón

    int m = text.length();
    int n = pattern.length();

    while (i < m) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == n) {
            positions.push_back(i - j); // Encontramos una ocurrencia de patrón que inicia en `i - j`
            j = lps[j - 1];
        } else if (i < m && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return positions;
}

void subsecuenciaConMayorRepeticion(
    str code,
    traVec& trs
) {

}

void KmpManager(strVec& mcodes, traVec& transmissions) {
    for (str mcode : mcodes) {
        std::cout << "Codigo: " << mcode << std::endl;
        
        for (Transmission trans : transmissions) {

            intVec patternPositions = Kmp(trans.content, mcode);
            int ocurrances = patternPositions.size();

            std::cout << trans.filename << " ==> " << ocurrances << " veces" << std::endl;

            for (int i = 0; i < patternPositions.size(); i++) {
                std::cout << patternPositions[i];

                if (i == patternPositions.size() - 1) {
                    std::cout << std::endl;
                } else {
                    std::cout << ", ";
                }
            }
        }

        // std::cout << "La subsecuencia mas encontrada es:" << std::endl;

        std::cout << "--------------" << std::endl;
    }

    std::cout << "==============" << std::endl;
}

#endif
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

tup<str, int, str> MostFrequentSubsequence( // <subsequence, frequency, filename>
    str code,
    traVec& trs
) {
    int maxFreq = 0;
    str bestSubsequence = "";
    str bestFile = "";

    // Generamos todas las subsecuencias quitando 1 carácter
    for (int i = 0; i < code.length(); i++) {
        str codeSubsequence = code.substr(0, i) + code.substr(i + 1);
        int totalFreq = 0;
        str currentFile = "";

        // Buscamos la subsecuencia en cada transmisión
        for (Transmission tr : trs) {
            intVec positions = Kmp(tr.content, codeSubsequence);
            int freq = positions.size();
            
            if (freq > maxFreq) {
                maxFreq = freq;
                bestSubsequence = codeSubsequence;
                bestFile = tr.filename;
            }
        }
    }

    return std::make_tuple(
        bestSubsequence,
        maxFreq,
        bestFile
    );
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

        auto [subsequence, frequency, filename] = MostFrequentSubsequence(mcode, transmissions);

        std::cout << "La subsecuencia mas encontrada es: " << subsequence << " con " << frequency << " veces en el archivo " << filename << std::endl;

        std::cout << "--------------" << std::endl;
    }

    std::cout << "==============" << std::endl;
}

#endif
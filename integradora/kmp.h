#ifndef KMP_MANAGER
#define KMP_MANAGER

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "common.h"
#include "aho_corasick.h"

using intVec = std::vector<int>;
using strVec = std::vector<str>;
using strPair = std::pair<str, str>;
using strPairVec = std::vector<strPair>;

// Complejidad: O(M), donde M es el tamaño del patrón.
intVec computeLps(str& pattern) {
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

// Complejidad: O(N + M), donde N es el tamaño del texto y M es el tamaño del patrón.
intVec kmp(str text, str pattern) {
    intVec positions;
    intVec lps = computeLps(pattern);

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

// Complejidad: O(L^2 + T*Q), donde L es la longitud del código, L^2 para construir el autómata de AhoCorasick,
// T es el número de transmisiones y Q es el tamaño de la transmisión.
tup<str, int, str> mostFrequentSubsequence( // <subsequence, frequency, filename>
    str code,
    traVec& trs
) {
    AhoCorasick ac;
    strVec subsequences;

    // Generamos todas las subsecuencias quitando 1 carácter
    for (int i = 0; i < code.length(); i++) {
        str sub = code.substr(0, i) + code.substr(i + 1);
        if (!sub.empty()) {
            ac.addPattern(sub);
            subsequences.push_back(sub);
        }
    }
    ac.buildSuffixLinks();

    int maxFreq = -1;
    str bestSubsequence = "";
    str bestFile = "";

    // Usamos un mapa para acumular las frecuencias de cada subsecuencia en todos los archivos
    std::map<str, int> totalFrequencies;
    for(const auto& sub : subsequences) {
        totalFrequencies[sub] = 0;
    }

    for (const auto& tr : trs) {
        std::map<str, int> freqsInFile = ac.search(tr.content);
        for (const auto& pair : freqsInFile) {
            if (pair.second > 0) { // Si la subsecuencia fue encontrada
                if (pair.second > maxFreq) {
                    maxFreq = pair.second;
                    bestSubsequence = pair.first;
                    bestFile = tr.filename;
                }
            }
        }
    }


    return std::make_tuple(
        bestSubsequence,
        maxFreq,
        bestFile
    );
}

// Complejidad: O(C * (L^2 + T*Q)), donde C es el número de códigos, L su longitud,
// T el número de transmisiones y Q la longitud de las transmisiones.
void kmpManager(strVec& mcodes, traVec& transmissions) {
    int mn = mcodes.size();

    for (int i = 0; i < mn; i++) { // O(M)
        str mcode = mcodes[i];
        std::cout << "Codigo: " << mcode << std::endl;
        
        for (Transmission trans : transmissions) { // O(K)

            intVec patternPositions = kmp(trans.content, mcode);
            int ocurrances = patternPositions.size();

            std::cout << trans.filename << " ==> " << ocurrances << " veces" << std::endl;

            for (int i = 0; i < patternPositions.size(); i++) { // O(E)
                std::cout << patternPositions[i];

                if (i == patternPositions.size() - 1) {
                    std::cout << std::endl;
                } else {
                    std::cout << ", ";
                }
            }
        }

        auto [subsequence, frequency, filename] = mostFrequentSubsequence(mcode, transmissions); // O(L^2 + T*Q)

        std::cout << "La subsecuencia mas encontrada es: " << subsequence << " con " << frequency << " veces en el archivo " << filename << std::endl;

        if (i < mn - 1) {
            std::cout << "--------------" << std::endl;
        } else { 
            std::cout << "==============" << std::endl;
        }
    }
}

#endif
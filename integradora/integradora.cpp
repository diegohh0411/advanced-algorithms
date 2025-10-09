// Diego Hernández Herrera, A01198786

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using str = std::string;
using strVec = std::vector<str>;
using intVec = std::vector<int>;
using readFilesReturnType = std::tuple<std::vector<str>, std::vector<std::pair<str, str>>>; // (mcode[], <filename, transmission>[])

void printStrVec(strVec& strV) {
    std::cout << "[" << std::endl;
    for (str e: strV) {
        std::cout << "\t" << e << std::endl;
    }
    std::cout << "]" << std::endl;
}

readFilesReturnType readFiles() {
    strVec mcodes = {};
    strVec maliciousCodeFilesToRead = { "mcode1.txt", "mcode2.txt", "mcode3.txt" };

    for (str fileName : maliciousCodeFilesToRead) {
        std::ifstream file(fileName);
        str line;

        while (std::getline(file, line)) {
            mcodes.push_back(line);
        }
    }

    std::vector<std::pair<str, str>> transmissions = {};
    strVec transmissionFilesToRead = { "transmission1.txt", "transmission2.txt", "transmission3.txt" };

    for (str fileName : transmissionFilesToRead) {
        std::ifstream file(fileName);
        str line;
        str content = "";

        while (std::getline(file, line)) {
            content += line;
        }

        transmissions.push_back(
            std::make_pair(
                fileName,
                content
            )
        );
    }

    return std::make_tuple(
        mcodes,
        transmissions
    );
}

intVec computeLPS(str& pattern) {
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

intVec KMP(str text, str pattern) {
    intVec positions;
    intVec lps = computeLPS(pattern);

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

int main() {
    auto [mcodes, transmissions] = readFiles();

    for (str mcode : mcodes) {
        std::cout << "Codigo: " << mcode << std::endl;
        
        for (std::pair trans : transmissions) {
            str filename = trans.first;
            str content = trans.second;

            str displayName = filename;
            if (!displayName.empty()) {
                displayName[0] = std::toupper(displayName[0]);
            }

            intVec patternPositions = KMP(content, mcode);
            int ocurrances = patternPositions.size();

            std::cout << displayName << " ==> " << ocurrances << " veces" << std::endl;

            for (int i = 0; i < patternPositions.size(); i++) {
                std::cout << patternPositions[i];

                if (i == patternPositions.size() - 1) {
                    std::cout << std::endl;
                } else {
                    std::cout << ", ";
                }
            }
        }
    }

    return 0;
}
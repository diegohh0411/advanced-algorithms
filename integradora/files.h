#ifndef FILES_MANAGER
#define FILES_MANAGER

#include <fstream>
#include <string>
#include <vector>
#include "common.h"

// Complejidad: O(N), donde N es el número total de líneas en los archivos a leer
std::tuple<strVec, traVec> readFiles() {
    strVec mcodes = {};
    strVec maliciousCodeFilesToRead = { "mcode.txt" };

    for (str fileName : maliciousCodeFilesToRead) {
        std::ifstream file(fileName);
        str line;

        while (std::getline(file, line)) {
            mcodes.push_back(line);
        }
    }

    traVec transmissions = {};
    strVec transmissionFilesToRead = { "transmission1.txt", "transmission2.txt", "transmission3.txt" };

    for (str fileName : transmissionFilesToRead) {
        std::ifstream file(fileName);
        str line;
        str content = "";

        while (std::getline(file, line)) {
            content += line;
        }

        Transmission tr(fileName, content);

        transmissions.push_back(
            tr
        );
    }

    return std::make_tuple(
        mcodes,
        transmissions
    );
}

#endif FILES_MANAGER
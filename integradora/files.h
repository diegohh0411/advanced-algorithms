#ifndef FILES_MANAGER
#define FILES_MANAGER

#include <fstream>
#include <string>
#include <vector>

using str = std::string;
using strVec = std::vector<str>;
using strPair = std::pair<str, str>;
using strPairVec = std::vector<strPair>;

std::tuple<std::vector<str>, strPairVec> readFiles() {
    strVec mcodes = {};
    strVec maliciousCodeFilesToRead = { "mcode.txt" };

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

#endif FILES_MANAGER
#ifndef COMMON_TYPES
#define COMMON_TYPES

#include <string>
#include <vector>

class Transmission {
public:
    std::string filename;
    std::string content;

    Transmission(std::string filename, std::string content) {
        this->filename = filename;
        this->content = content;
    }
};

using str = std::string;

using strVec = std::vector<str>;
using traVec = std::vector<Transmission>;



#endif
#ifndef COMMON_TYPES
#define COMMON_TYPES

#include <string>
#include <vector>
#include <tuple>

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

template<typename... Args>
using tup = std::tuple<Args...>;

using strVec = std::vector<str>;
using traVec = std::vector<Transmission>;



#endif
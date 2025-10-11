#ifndef COMMON_TYPES
#define COMMON_TYPES

#include <string>
#include <vector>
#include <tuple>

class Transmission {
public:
    std::string filename;
    std::string content;

    // O(1), esta función es de tiempo constante
    Transmission(std::string filename, std::string content) {
        this->filename = filename;
        this->content = content;
    }
};

using str = std::string;

template<typename... Args>
using tup = std::tuple<Args...>;

template <typename... Args>
using vec = std::vector<Args...>;

using intVec = vec<int>;
using strVec = vec<str>;
using traVec = vec<Transmission>;



#endif
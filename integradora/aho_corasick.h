#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include "common.h"

// Estructura de un nodo en el Trie del autómata
struct Node {
    std::map<char, int> next;       // Nodos hijos
    int suffixLink = -1;            // Suffix link
    vec<int> patternIndices; // Índices de los patrones que terminan en este nodo
};

class AhoCorasick {
public:
    vec<Node> trie;
    vec<str> patterns;

    AhoCorasick() {
        trie.emplace_back(); // Nodo raíz
    }

    // Agrega un patrón al Trie
    void addPattern(const str& pattern) {
        int v = 0;
        for (char ch : pattern) {
            if (trie[v].next.find(ch) == trie[v].next.end()) {
                trie[v].next[ch] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[ch];
        }
        trie[v].patternIndices.push_back(patterns.size());
        patterns.push_back(pattern);
    }

    // Construye los suffix links usando BFS
    void buildSuffixLinks() {
        std::queue<int> q;
        q.push(0);

        while(!q.empty()){
            int v = q.front();
            q.pop();

            for(auto const& [key, val] : trie[v].next){
                int child_node = val;
                int p = trie[v].suffixLink;
                while(p != -1 && trie[p].next.find(key) == trie[p].next.end()){
                    p = trie[p].suffixLink;
                }
                if(p != -1){
                    trie[child_node].suffixLink = trie[p].next[key];
                } else {
                    trie[child_node].suffixLink = 0;
                }
                
                int suffix_node = trie[child_node].suffixLink;
                if (suffix_node != -1) {
                    for(int index : trie[suffix_node].patternIndices) {
                        trie[child_node].patternIndices.push_back(index);
                    }
                }
                q.push(child_node);
            }
        }
    }

    // Busca todos los patrones en un texto y devuelve su frecuencia
    std::map<str, int> search(const str& text) {
        std::map<str, int> result;
        for(const auto& p : patterns) {
            result[p] = 0;
        }

        int v = 0;
        for (char ch : text) {
            while (v != -1 && trie[v].next.find(ch) == trie[v].next.end()) {
                v = trie[v].suffixLink;
            }
            if (v != -1) {
                v = trie[v].next[ch];
            } else {
                v = 0;
            }
            
            if (v != -1) {
                for (int patternIndex : trie[v].patternIndices) {
                    result[patterns[patternIndex]]++;
                }
            }
        }
        return result;
    }
};

#endif

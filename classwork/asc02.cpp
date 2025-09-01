// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>

// Complejidad temporal: O(n) donde n es la longitud del patrón
// Complejidad espacial: O(n) para almacenar el arreglo LPS
std::vector<int> compute_lps_array(std::string& pattern) {
    int n = pattern.size();
    std::vector<int> lps(n);

    int len = 0; // We maintain a variable len, initialized to 0, which keeps track of the length of the previous longest prefix suffix.
    int i = 1; 

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // Fall back in the pattern.
                len = lps[len - 1]; 
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;    
}

// Complejidad temporal: O(n) donde n es el tamaño del vector
// Complejidad espacial: O(1) no requiere espacio adicional
template <typename T>
void print_vector(std::vector<T>& vec) {
    std::cout << "[ ";
    for (int val : vec)
        std::cout << val << "\t";
    std::cout << "]" << std::endl;
}

// Complejidad temporal: O(n+m) donde n es la longitud del texto y m es la longitud del patrón
// Complejidad espacial: O(m) para almacenar el arreglo LPS más O(k) para almacenar resultados
std::vector<int> search(std::string& pattern, std::string& text) {
    int n = text.length();
    int m = pattern.length();

    std::vector<int> lps = compute_lps_array(pattern);
    
    std::vector<int> result;

    int i = 0, j = 0; // i is the index of the traverse along the text, while j is the index of the pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            if (j == m) { // If the entire pattern is matched, store the start index in result.
                result.push_back(i - j);

                j = lps[j - 1];
            }
        } else { // If there is a mismatch, use LPS value of the previous index to avoid redundant comparisons.equal" << std::endl;
            if (j != 0)
                j = lps[j - 1];
            else 
                i++;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Complejidad temporal: O(m) donde m es la longitud del texto
// Complejidad espacial: O(m) para almacenar el vector de booleanos
std::vector<bool> tell_which_to_include(std::string& text, std::vector<int>& result, int pattern_size) {
    int m = text.size();
    std::vector<bool> indexes(m, true);

    int nextIndex = result.back();
    result.pop_back();

    for (int i = 0; i < m; i++) {
        if (i == nextIndex) {
            for (int j = i; j < i + pattern_size; j++)
                indexes[j] = false;
            nextIndex = result.back();
            result.pop_back();
        }
    }

    return indexes;
}

// Complejidad temporal: O(n+m) determinada por la función search
// Complejidad espacial: O(n+m) para almacenar los vectores de resultados
int main() {
    std::string text, pattern;

    std::cin >> text;
    std::cin >> pattern;

    std::vector<int> result = search(pattern, text);
    std::vector<bool> indexes = tell_which_to_include(text, result, pattern.size());

    for (int i = 0; i < text.size(); i++) {
        if (indexes[i])
            std::cout << text[i];
    }
    std::cout << std::endl;
}
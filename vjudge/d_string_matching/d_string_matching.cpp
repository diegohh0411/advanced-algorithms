// Diego Hernández Herrera, A01198786
#include <iostream>
#include <string>
#include <vector>

// Complejidad: O(m) donde m es la longitud del patron
std::vector<int> calcularLPS(const std::string& patron) {
    int m = patron.length();
    std::vector<int> lps(m, 0);
    int length = 0;
    int i = 1;

    while (i < m) {
        if (patron[i] == patron[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// O(n + m)
int main() {
    std::string text, pattern;
    std::cin >> text >> pattern;

    int i = 0; // pointer for text
    int j = 0; // pointer for pattern

    int n = text.length();
    int m = pattern.length();

    if (m == 0 || n == 0 || m > n) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int count = 0;

    std::vector<int> lps = calcularLPS(pattern);

    while (i < n) { // O(n)
        // Si los caracteres en las posiciones actuales coinciden, avanzamos ambos punteros.
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        // Si 'j' es igual a la longitud del patrón, hemos encontrado una ocurrencia completa.
        if (j == m) {
            count++; // Incrementamos el contador de ocurrencias.
            // Usamos el array LPS para continuar la búsqueda de la siguiente posible ocurrencia.
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            // Si hay una discrepancia y aún no hemos terminado de recorrer el texto.
            if (j != 0) {
                j = lps[j - 1];
            } else {
                // Si la discrepancia ocurre en el primer carácter del patrón (j == 0),
                // no podemos retroceder más en el patrón, así que solo avanzamos en el texto.
                i++;
            }
        }
    }

    std::cout << count << std::endl;

    return 0;
}

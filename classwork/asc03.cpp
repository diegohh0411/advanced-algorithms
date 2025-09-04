// Diego Hernández Herrera, A01198786
// ASC03 - Algoritmo de Manacher

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

// Complejidad temporal: O(n)
// Complejidad espacial: O(n)
static std::string preprocess(const std::string &s) {
	if (s.empty()) return "^$"; // sentinelas para evitar checar límites
	std::string t = "^";       // inicio
	for (char c : s) {
		t += "#";
		t += c;
	}
	t += "#$"; // fin
	return t;
}

// Devuelve el palíndromo más largo en s usando Manacher
// Complejidad temporal: O(n)
// Complejidad espacial: O(n)
static std::tuple<int, int> manacher_longest_palindrome(const std::string &s) { // Regresa el índice donde inicia el palíndromo y el índice donde termina el palíndromo
	std::string t = preprocess(s);
	int n = (int)t.size();
	std::vector<int> p(n, 0); // radios de palíndromos en cadena transformada
	int center = 0, right = 0;

	for (int i = 1; i < n - 1; ++i) {
		int mirror = 2 * center - i; // índice espejo respecto a center
		if (i < right) {
			p[i] = std::min(right - i, p[mirror]);
		}

		// Expansión alrededor de i
		while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
			++p[i];
		}

		// Actualizar centro y borde derecho si se expandió más allá de right
		if (i + p[i] > right) {
			center = i;
			right = i + p[i];
		}
	}

	// Encontrar el máximo
	int maxLen = 0;
	int centerIndex = 0;
	for (int i = 1; i < n - 1; ++i) {
		if (p[i] > maxLen) {
			maxLen = p[i];
			centerIndex = i;
		}
	}

	int start = (centerIndex - maxLen) / 2; // mapear a índices de s
    return { start, start + maxLen };
}

// Complejidad temporal: O(n)
// Complejidad espacial: O(n)
int main() {
	std::string s;

	if (!(std::cin >> s)) {
		std::cout << 0 << "\n\n"; // sin entrada, imprimir longitud 0 y línea vacía
		return 0;
	}

    int sn = s.size();
    int i, j;
	std::tie(i, j) = manacher_longest_palindrome(s);

    std::string left_part =  s.substr(0, i);
    std::string middle_part = s.substr(i, j - i);
    std::string right_part = s.substr(j, sn - j);

    if (left_part.size() > 0)
        std::cout << "Left:\t" << left_part << std::endl;
    else
        std::cout << "Left:\tNO LEFT PART" << std::endl;
    
    if (middle_part.size() > 0)
        std::cout << "Middle:\t" << middle_part << std::endl;
    else
        std::cout << "Middle:\tNO MIDDLE PART" << std::endl;

    if (right_part.size() > 0)
        std::cout << "Right:\t" << right_part << std::endl;
    else  
        std::cout << "Right:\tNO RIGHT PART" << std::endl;

	return 0;
}


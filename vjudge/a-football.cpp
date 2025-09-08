// Diego Hernandez Herrera, A01198786

#include <iostream>
#include <string>

// Complejidad temporal: O(n), donde n es la longitud de la cadena de entrada
// Complejidad espacial: O(1), uso constante de memoria adicional
int main() {
    int consecutive_characters = 0;
    
    std::string input;
    std::cin >> input;
    char& last_char = input[0];

    for (int i = 1; i < input.size(); i++) {
        char& cc = input[i]; // Current Char
        
        if (last_char == cc)
            consecutive_characters++;
        else 
            consecutive_characters = 0;

        if (consecutive_characters == 6) {
            std::cout << "YES";
            return 0;
        }

        last_char = cc;
    }

    std::cout << "NO";
    return 0;
}
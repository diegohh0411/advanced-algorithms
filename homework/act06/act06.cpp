// Diego Hernández Herrera, A01198786
// Comentario: No sé si estas funciones sean las más eficientes, pero las hice a mano y sin pedirle ayuda a ninguna Inteligencia Artificial más que para ayudarme a determinar las complejidades. Pero toda la lógica la diseñé yo; tanto así que podría haber escrito esto sin conexión a internet.

#include <iostream>
#include <string>


// Time Complexity: O(n * m * min(n, m)), where n and m are the lengths of the input strings.
// Space Complexity: O(1), only a few variables are used (no extra arrays).
int calculateLCS() { // Calculate the LCS (Longest Common Substring)
    std::string a;
    std::string b;

    std::cin >> a;
    std::cin >> b;

    std::string& shortest = (a.size() < b.size()) ? a : b;
    std::string& longest = (a.size() < b.size()) ? b : a;

    int sn = shortest.size();
    int ln = longest.size();

    int highest_sliding_index = -1;

    for (int i = 0; i < ln; i++) {
        for (int j = 0;  j < sn; j++) {
            int sliding_index = 0;

            // std::cout << "{ i: " << i << ", j: " << j << " }" << std::endl;
            while (
                longest[i + sliding_index] == shortest[j + sliding_index] &&
                (i + sliding_index) < ln && (j + sliding_index) < sn
            ) {
                // std::cout << "\tComparing: '" << longest[i + sliding_index] << "' with '" << shortest[j + sliding_index] << "'" << std::endl;
                sliding_index++;
                // std::cout << "\tsliding_index is now: " << sliding_index << std::endl; 
            }

            if (sliding_index > highest_sliding_index)
                highest_sliding_index = sliding_index;
        }
    }

    return highest_sliding_index;
}

// Time Complexity: O(n * (length of a + length of b)), where n is the number of cases.
// Space Complexity: O(1), aside from input strings.
int main() {
    int n; // This represents the number of cases
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cout << "Case " << (i + 1) << ": " << calculateLCS() << std::endl;
}
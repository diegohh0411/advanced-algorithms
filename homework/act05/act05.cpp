// Diego Hernández Herrera, A01198786
// Este código requiere C++17 al menos. Yo lo escribí compilando para C++20.

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

// Complejidad temporal: O(a + b)
// Complejidad espacial: O(a + b)
// Lee la entrada y crea tres vectores con los valores dados
std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> get_input(int a, int b) {
    std::vector<int> nums1, nums2, combo;
    int input_value;

    for (int i = 0; i < a; i++) {
        std::cin >> input_value;
        nums1.push_back(input_value);
    }

    for (int i = 0; i < b; i++) {
        std::cin >> input_value;
        nums2.push_back(input_value);
    }

    for (int i = 0; i < (a + b); i++) {
        std::cin >> input_value;
        combo.push_back(input_value);
    }

    return std::make_tuple(nums1, nums2, combo);
}

// Complejidad temporal: O(2^(n1 + n2)) en el peor caso
// Complejidad espacial: O(n1 + n2) para la pila de recursión
// Función recursiva de backtracking que determina si es posible formar la secuencia combo
// usando elementos de nums1 y nums2 en orden
bool is_possible(
    std::vector<int>& nums1, int& i1, int& n1,
    std::vector<int>& nums2, int& i2, int& n2,
    std::vector<int>& combo, int& ic, int& nc
) {
    if (ic >= nc) {
        return true; // Si hemos recorrido todo el combo esperado hasta el final, significa que sí hay manera de organizar los vagones de los trenes.
    }

    int expected = combo[ic];

    if (i1 < n1 && nums1[i1] == expected) {
        i1++;
        ic++;

        if (is_possible(nums1, i1, n1, nums2, i2, n2, combo, ic, nc))
            return true; // Si ya se encontró una solución a través de esta rama, regresar verdadero.

        // Si no se encontró solución por esta rama, backtrack los índices.
        i1--;
        ic--;
    }

    if (i2 < n2 && nums2[i2] == expected) {
        i2++;
        ic++;

        if (is_possible(nums1, i1, n1, nums2, i2, n2, combo, ic, nc))
            return true;

        // backtrack
        i2--;
        ic--;
    }

    // Si ninguno de las dos ramas funcionó, este path falla.
    return false;
}

// Complejidad temporal: O(k * 2^(n1 + n2)) donde k es el número de casos de prueba
// Complejidad espacial: O(n1 + n2) para almacenar los vectores y la pila de recursión
// Función principal que coordina la lectura de entrada y llama al algoritmo de verificación
int main() {
    int n1;
    int n2;

    std::cin >> n1 >> n2;
    
    while (n1 != 0 && n2 != 0) {
        auto [nums1, nums2, combo] = get_input(n1, n2);
        int i1 = 0;
        int i2 = 0;
        int ic = 0;
        int nc = combo.size();

        if (is_possible(nums1, i1, n1, nums2, i2, n2, combo, ic, nc)) { 
            std::cout << "possible" << std::endl;
        } else {
            std::cout << "not possible" << std::endl;
        }

        std::cin >> n1 >> n2;
    }

}
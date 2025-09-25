// Sum_of_Subsets - Backtracking
// Matrícula: A00135997
// Nombre: Luis Humberto González Guerra

#include <iostream>
#include <vector>
#include <algorithm>

// Complejidad:
void sum_of_subset(
    int i, 
    int acum, 
    int total, 
    int n,
    int valor,
    std::vector<int>& obj, 
    std::vector<bool>& include
) {
    if (
        acum + total >= valor // Todavía no se pasa del valor
        && (acum == valor || acum + obj[i + 1] <= valor)
    ) {
        if (acum == valor) {
            std::cout << "Solución: ";
            for (int j = 0; j < n; j++) {
                if (include[j])
                    std::cout << j << " ";
            }
            std::cout << std::endl;
        } else {
            include[i + 1] = true;
            sum_of_subset(i + 1, acum+obj[i+1], total - obj[i+1], n, valor, obj, include);

            include[i+1] = false;
            sum_of_subset(i+1, acum, total - obj[i+1], n, valor, obj, include);
        }
    }
}

int main() {
    // n = Cantidad de objetos o valores
    // VALOR = Valor a buscar
    int n, VALOR;
    // include = es un vector que represnta los objetos que SI
    // debes incluir
    std::vector<bool> include;
    // obj = Los valores de los objetos
    std::vector<int> obj;
    std::cin >> n >> VALOR;

    int dato, total = 0;
    for (int i=0; i<n; i++){
        std::cin >> dato;
        obj.push_back(dato);
        total += dato;
        include.push_back(false);
    }

    sort(obj.begin(), obj.end());

    sum_of_subset(-1, 0, total, n, VALOR, obj, include);
}
/*
5 21
10
6
5
16
11
*/
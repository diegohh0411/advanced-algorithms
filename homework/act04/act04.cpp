// Diego Hernández Herrera, A01198786
// Escrito el domingo 24 de agosto

#include <iostream>
#include <vector>

using Row = std::vector<int>;
using Matrix = std::vector<Row>;

// Time complexity: O(n * m)
// Spatial complexity: O(1)
int solve(Matrix& matr) {
    int n = matr.size();
    int m = matr[0].size();

    // Vamos a llenar la primera fila y columna, porque ellos solo tienen 1 vecino en 1 dirección.

    // Time complexity: O(n)
    for (int j = 1; j < n; j++)
        matr[j][0] = matr[j][0] + matr[j - 1][0];

    // Time complexity: O(m)
    for (int i = 1; i < m; i++) 
        matr[0][i] = matr[0][i] + matr[0][i - 1];

    // Ahora sí ejecutamos el algoritmo que suma ambos vecinos al resto de las ubicaciones.

    // Time complexity: O(n * m)
    for (int j = 1; j < n; j++) {
        for (int i = 1; i < m; i++) {
            matr[j][i] = matr[j][i] + std::min(
                matr[j - 1][i],
                matr[j][i - 1]
            );
        }
    }

    return matr[n - 1][m - 1];
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Matrix matrix(n, std::vector<int>(m));

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            std::cin >> matrix[j][i];
        }
    }

    std::cout << solve(matrix) << std::endl;
}
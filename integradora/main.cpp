// Diego Hernández Herrera, A01198786

#include <iostream>

#include "kmp.h"
#include "manacher.h"
#include "files.h"
#include "lcs.h"
#include "common.h"

// Complejidad: O(
//  (N) +
//  O(C * (L^2 + T*Q)) +
//  (T * Q) +
//  (F + G)
int main() {
    auto [mcodes, transmissions] = readFiles(); // Complejidad: O(N)

    kmpManager(mcodes, transmissions); // O(C * (L^2 + T*Q)), donde C es el número de códigos, L su longitud, T el número de transmisiones y Q la longitud de las transmisiones.
    manacherManager(transmissions); // O(T * Q), donde T es el número de transmisiones y Q es la longitud de cada transmisión
    lcsManager(transmissions); // O(F + G), donde F y G son los tamaños de los textos comparados

    return 0;
}
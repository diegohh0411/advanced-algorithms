// Diego Hernández Herrera, A01198786

#include <iostream>

#include "kmp.h"
#include "manacher.h"
#include "files.h"
#include "lcs.h"
#include "common.h"

// Complejidad: O(
//  (N) +
//  (M * [(K * E) + (L * K (C + P)))]) +
//  (T * Q) +
//  (F + G)

int main() {
    auto [mcodes, transmissions] = readFiles(); // Complejidad: O(N)

    KmpManager(mcodes, transmissions); // O(M * [(K * E) + (L * K (C + P)))]), donde M es la cantidad de códigos maliciosos, E es el número de patrones encontrados, L es la longitud del mcode, K es el número de transmisiones y C es la longitud del contenido cada transmisión y P es la longitud de la subsecuencia.
    ManacherManager(transmissions); // O(T * Q), donde T es el número de transmisiones y Q es la longitud de cada transmisión
    LcsManager(transmissions); // O(F + G), donde F y G son los tamaños de los textos comparados

    return 0;
}
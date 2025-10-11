# Actividad Integradora de Diego Hernández

Esta Actividad Integradora la hice por mi cuenta, ya que quería aprender y poner manos a la obra. Utilicé muchos de los algoritmos vistos en clase para resolver el problema, además investigué la implementación de otro algoritmo por mi cuenta.

Para empezar, utilicé el algoritmo de Knuth-Morris-Pratt para buscar patrones de códigos maliciosos en las transmisiones. Implementé la función `computeLps` que construye el arreglo de prefijos-sufijos en tiempo O(N), y luego la función `kmp` que realiza la búsqueda del patrón en el texto con complejidad O(N + M). Este algoritmo me permitió encontrar eficientemente todas las posiciones donde aparece cada código malicioso en cada transmisión.

Además, investigué e implementé el algoritmo de Aho-Corasick para resolver el problema de encontrar la subsecuencia más frecuente. Este algoritmo construye un autómata basado en una estructura Trie con suffix links, permitiendo buscar múltiples patrones simultáneamente en un texto. Lo apliqué generando todas las subsecuencias posibles de cada código (quitando un carácter a la vez) y buscándolas en todas las transmisiones de forma eficiente, logrando una complejidad de O(L² + T*Q).

Para encontrar el palíndromo más largo, utilicé el algoritmo de Manacher, que tiene una complejidad lineal O(N). Este algoritmo expande el string insertando caracteres especiales '#' entre cada carácter original, y luego utiliza la información de palíndromos previamente calculados para evitar comparaciones redundantes, encontrando el palíndromo más largo en una sola pasada.

Finalmente, para encontrar el substring común más largo entre pares de transmisiones, implementé el algoritmo de Longest Common Substring usando programación dinámica. Creé una matriz donde `dp[i][j]` representa la longitud del substring común que termina en las posiciones i y j de ambos strings, alcanzando una complejidad de O(F * G) donde F y G son las longitudes de los textos comparados.

## Análisis de Complejidad Computacional

### Algoritmo de Knuth-Morris-Pratt
- **`computeLps(pattern)`**: O(M), donde M es la longitud del patrón. Esta función construye el arreglo de prefijos-sufijos recorriendo el patrón una sola vez.
- **`kmp(text, pattern)`**: O(N + M), donde N es la longitud del texto y M es la longitud del patrón. El algoritmo recorre el texto una vez y utiliza el arreglo LPS para evitar comparaciones redundantes.
- **`kmpManager(mcodes, transmissions)`**: O(C * (L² + T*Q)), donde C es el número de códigos maliciosos, L es la longitud promedio de los códigos, T es el número de transmisiones y Q es la longitud de cada transmisión. La complejidad L² viene del algoritmo Aho-Corasick usado para encontrar subsecuencias.

### Algoritmo de Aho-Corasick
- **`addPattern(pattern)`**: O(M), donde M es la longitud del patrón que se está agregando al Trie.
- **`buildSuffixLinks()`**: O(K * Σ), donde K es el número total de nodos en el Trie y Σ es el tamaño del alfabeto. En la práctica, esto es O(L²) donde L es la longitud total de todos los patrones.
- **`search(text)`**: O(N + Z), donde N es la longitud del texto y Z es el número total de ocurrencias de todos los patrones encontrados.
- **`mostFrequentSubsequence(code, trs)`**: O(L² + T*Q), donde L es la longitud del código (L² para generar todas las subsecuencias y construir el autómata), T es el número de transmisiones y Q es la longitud de cada transmisión.

### Algoritmo de Manacher
- **`manacherPreprocess(s)`**: O(N), donde N es la longitud del string original. Simplemente inserta caracteres '#' entre cada carácter.
- **`manacher(s)`**: O(N), donde N es la longitud del string. A pesar de tener ciclos anidados, el algoritmo utiliza la propiedad de simetría de los palíndromos para garantizar que cada posición se procesa en tiempo constante.
- **`manacherManager(transmissions)`**: O(T * Q), donde T es el número de transmisiones y Q es la longitud de cada transmisión.

### Algoritmo de Longest Common Substring
- **`longestCommonSubstring(s1, s2)`**: O(F * G), donde F y G son las longitudes de los dos strings a comparar. Utiliza una matriz de programación dinámica de tamaño F×G.
- **`lcsManager(trs)`**: O(F * G), donde F y G son las longitudes de los textos más largos comparados. Se ejecuta tres veces para las tres combinaciones posibles de transmisiones.

### Función Principal
- **`readFiles()`**: O(N), donde N es el número total de líneas en todos los archivos leídos.
- **`main()`**: O(N + C * (L² + T*Q) + T*Q + F*G)
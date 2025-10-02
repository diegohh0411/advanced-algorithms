/*
  Matricula: A01198786
  Nombre: Diego Hernández Herrera
*/

#include <iostream>
#include <vector>
#include <map>

/**
 * Pregunta acerca del problema: qué pasa si en el vector NO existe ni un solo par de números enteros iguales? Por ejemplo: ´[1 2 3]`. El algoritmo debería de regresar true or false? Yo estoy asumiendo que debería de regresar `false`, porque las instrucciones dicen "encuentra si existen dos enteros iguales almacenados en el vector...". O sea que si no existen al menos un par de enteros iguales la respuesta es: no, no existen. False.
 */

// Complejidad: O(n * k) donde n es la cantidad de elementos en el vector y k la cantidad de elementos distintos en el vector
bool iguales(std::vector<int> &d, int k){
  int n = d.size();
  if (n == 0) return false; // Regresamos `false` porque no existe un par de enteros iguales que cumplan con los parámetros.

  std::map<int, int> diffs; // Este mapa nos ayudará a mantener un registro de la diferencia del índice del último entero contra el índice actual del for loop.
  diffs[d[0]] = 0;

  for (int i = 1; i < d.size(); i++) { // O(n) donde n es el tamaño del vector
    for (const auto& pair : diffs) { // O(k) donde k es la cantidad de enteros distintos que hay en el vector
      diffs[pair.first] += 1; // Cada vez que avanzamos en el for loop, la diferencia de índices con cada entero incrementa también.
    }

    int cv = d[i]; // cv = current value, el valor actual
    if (diffs.find(cv) == diffs.end()) { // Si el entero no existe en el mapa, es la primera aparición. Así que lo añadimos al mapa con una diferencia de 0.
      diffs[cv] = 0;
    } else { // Si sí está en el mapa´, checamos que la condición se cumpla. Si al menos un par de enteros tiene una diferencia de índices igual o menor que k, entonces sí exíste el requisito o condición y podemos regresar true.
      if (diffs[cv] <= k) return true;
      diffs[cv] = 0; // Si no se cumple la condición, seguimos adelante en espera de otro entero igual y reseteamos la diferencia del índice.
    }
  }

	return false;
}

// Complejidad: O(n + n * k) donde n es la cantidad de elementos en el vector y k la cantidad de elementos distintos en el vector
int main(){
	int n, k;
	std::cin >> n >> k;
	std::vector<int> datos(n);
	for (int i=0; i<n; i++){ // O(n)
		std::cin >> datos[i];
	}

  std::cout << (iguales(datos, k)? "true" : "false") << std::endl; // O(n * k)
}

/*
Ejemplo 1
4 3
1 2 3 1

Ejemplo 2
4 1
1 0 1 1

Ejmplo 3
6 2
1 2 3 1 2 3

*/
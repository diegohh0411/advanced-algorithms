// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

// Voy a explicar un poco cómo solucioné este problema. Realmente, para cada ruta solo nos interesa saber cuál es el primer autobús que llega después de que Serval ya llegó. No nos sirve saber cuáles llegar antes que Serval a la estación. Tampoco nos interesan todos los que llegan después del primer autobús, porque Serval tomará el primero que llegue. Entonces solo tengo que calcular en qué tiempo llegará el primer autobús de cada ruta, y luego ordenar estos primeros autobuses según sus tiempos de llegada. Y así sabré cuál es el primero que llegará después de que Serval llegue.

// Complejidad temporal en el peor de los casos: O(n*t + n log n)
int main() {
    // The tuples will be (t, r) where t is the time at which the bus arrives at the station and r the route it belongs to.
    std::vector<std::tuple<int, int>> times;

    int n, t;
    std::cin >> n >> t;

    // Complejidad del loop: O(n*t)
    for (int i = 0; i < n; i++) { // O(n)
        int si, di;
        std::cin >> si >> di;

        int ct = si; // Current time of the bus route.
        while (ct < t) { // Complejidad en el peor de los casos, cuando si = 0 y di = 1, O(t)
        // While we don't have the first bus that arrives after Serval has already arrived, we want to calculate the next bus that will arive using `ct` and `di`.
            ct += si;
        }

        std::tuple<int, int> first_bus_to_arrive_after_serval(ct, i);
        times.push_back(first_bus_to_arrive_after_serval);
    }

    std::sort(times.begin(), times.end()); // O(n log n)

    auto [time, route] = times.front();

    std::cout << (route + 1) << std::endl;
}
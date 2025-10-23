// Diego Hernández Herrera, A01198786

#include <unordered_set>
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 100

struct color{
    int conex; // amount of connections
    int vtx; // vertex no. 
};

// Complejidad: O(1)
// Comparador para ordenar según el vertex no., y luego según el amount of connections
bool my_cmp(const color &c1, const color &c2){
    if (c1.conex == c2.conex){
        return c1.vtx < c2.vtx;
    }
    return c1.conex > c2.conex;
}

// Complejidad: O(m)
void leerArcos(bool matAdj[MAX][MAX], std::vector<color> &vtxColor, int m){
    int u, v;
    for (int i=0; i<m; i++){
        std::cin >> u >> v; // Inputs con base uno
        u--; // Convertir a base cero
        v--; // Convertir a base cero
        matAdj[u][v] = matAdj[v][u] = true;
        vtxColor[u].conex++;
        vtxColor[v].conex++;
    }
}

// Complejidad: O(k) donde k es el tamaño del conjunto, en el peor caso O(n)
bool canColor(bool matAdj[MAX][MAX], std::unordered_set<int> &conj, int j){
    for (int num : conj){
        if (matAdj[num][j]){
            return false;
        }
    }
    return true;
}

// Complejidad: O(n^2)
std::vector<int> colorGraph(bool matAdj[MAX][MAX], std::vector<color> &vtxColor){
    int numColor = 0;
    int n = vtxColor.size();
    std::vector<int> colored(n, 0); // Todos los vertex empiezan sin color (no. 0)
    for (int a = 0; a < n; a++){
        int i = vtxColor[a].vtx;
        if (!colored[i]){
            colored[i] = ++numColor;
            std::unordered_set<int> conj;
            conj.insert(i);
            for (int b = a + 1; b < n; b++){
                int j = vtxColor[b].vtx;
                if(!colored[j] && canColor(matAdj, conj, j)){
                    colored[j] = numColor;
                    conj.insert(j);
                }
            }
        }
    }

    return colored;
}

// Complejidad: O(n * m + n log n) donde n es el número de vértices y m es el número de arcos
int main(){
    int n, m;
    std::cin >> n >> m;
    bool matAdj[MAX][MAX] = {false};

    std::vector<color> vtxColor(n);
    color c;
    for (int i = 0; i < n; i++){
        c.conex = 0;
        c.vtx = i;
        vtxColor[i] = c;
    }
    leerArcos(matAdj, vtxColor, m);
    sort(vtxColor.begin(), vtxColor.end(), my_cmp);

    std::vector<int> colored = colorGraph(matAdj, vtxColor);
    for (int i = 0; i < n; i++){
        std::cout << "Vertex " << i+1 << " with color " << colored[i] << std::endl;
    }

    return 0;
}

/*
7 11
1 2
1 3
1 4
2 3
2 5
3 4
3 5
4 5
4 6
5 7
6 7
*/
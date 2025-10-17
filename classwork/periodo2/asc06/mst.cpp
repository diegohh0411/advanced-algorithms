
// MST (Primm y Kruskal)
// Autor: Diego Hernández Herrera
// Matrícula: A01198786
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

#define INF INT_MAX

using namespace std;

struct Transition { // Agregué esto porque así me resulta más sencillo recordar qué propiedad significa qué.
	int cost, destination;

	Transition(int c, int d) {
		this->cost = c;
		this->destination = d;
	}
};

struct Graph {
	// V = Cantidad de nodos (Vertex)
	// E = Cantidad de Arcos (Edges)
	int V, E, costMSTPrim, costMSTKruskal;
	vector<pair<int, pair<int, int>>> edges;	// Utilizar en Kruskal
	vector<vector<Transition>> adjList;		// Lista de Adj utilizado en Prim
	vector<pair<int, int>> selectedEdgesK;		// Arcos seleccionados por Kruskal
	vector<pair<int, int>> selectedEdgesP;		// Arcos seleccionados por Prim
	Graph(int V, int E){
		this->V = V;
		this->E = E;
		adjList.resize(V);
		costMSTKruskal = costMSTPrim = 0;
	}
	// u = salida del arco
	// v = llegada del arco
	// w = costo del arco
	void addEdge(int u, int v, int w){
		edges.push_back({w, {u, v}}); // first = costo, second = conexión

		Transition t(w, v);
		adjList[u].push_back(t);
	}
	void load();
	void print();
	void kruskalMST();
	void primMST();
	void printEdgesP();
	void printEdgesK();
};


//Disjoint Sets (Union-Find)
struct DisjointSets{
	int *parent, *rank;
	int n;
	DisjointSets(int n){
		this->n = n;
		parent = new int[n+1];
		rank = new int[n+1];
		for (int i=0; i<=n; i++){
			rank[i] = 0;
			parent[i] = i;
		}
	}
	// Para encontrar el parent de 'u'
	int find(int u){
		if (u != parent[u]){
			parent[u] = find(parent[u]);
		}
		return parent[u];
	}
	void merge(int x, int y){
		x = find(x);
		y = find(y);
		if (rank[x] > rank[y]){
			parent[y] = x;
		}
		else{
			parent[x] = y;
		}
		if (rank[x] == rank[y]){
			rank[y]++;
		}
	}
};

void Graph::load(){
	int a, b, c;
	for (int i=0; i<E; i++){
		cin >> a >> b >> c;
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void Graph::print(){
	cout << "Adjacent List: " << endl;
	for (int i=0; i<V; i++){
		cout << i << ": ";
		for (int j=0; j<adjList[i].size(); j++){
			cout << "(cost: " << adjList[i][j].cost << ", destination: " << adjList[i][j].destination << ") ";
		}
		cout << endl;
	}
}

// Complejidad: O(V^2 * E)
void Graph::primMST(){
	vector<int> Y = {};  // Visited nodes
	vector<int> W = {};  // Unvisited nodes
	
	// Initialize W with all vertices
	for (int i = 0; i < V; i++) {
		W.push_back(i);
	}

	// Start with vertex 0
	int startingNode = 0;
	Y.push_back(startingNode);
	W.erase(remove(W.begin(), W.end(), startingNode), W.end());

	while (W.size() > 0) {
		int minCost = INF;
		int bestSource = -1;
		int bestDestination = -1;

		// Find the minimum cost edge from any node in Y to any node in W
		for (int y : Y) {
			for (const auto& neighbor : adjList[y]) {
				int dest = neighbor.destination;
				int cost = neighbor.cost;
				
				// Check if destination is in W (unvisited)
				if (find(W.begin(), W.end(), dest) != W.end()) {
					if (cost < minCost) {
						minCost = cost;
						bestSource = y;
						bestDestination = dest;
					}
				}
			}
		}

		// If we found a valid edge
		if (bestDestination != -1) {
			// Add the edge to selected edges
			selectedEdgesP.push_back({ bestSource, bestDestination });
			
			// Add cost to total
			costMSTPrim += minCost;
			
			// Move destination from W to Y
			Y.push_back(bestDestination);
			W.erase(remove(W.begin(), W.end(), bestDestination), W.end());
		} else {
			// No more reachable nodes (disconnected graph)
			break;
		}
	}
}

void Graph::printEdgesP(){
	cout << "Selected Edges Prim: ";
	for (auto it:selectedEdgesP){
		cout << "(" << it.first << ", " << it.second << ") ";
	}
	cout << endl;
}

// Complejidad: O(E log E)
void Graph::kruskalMST(){
	// Sort edges by cost
	sort(edges.begin(), edges.end());
	
	// Create disjoint sets
	DisjointSets ds(V);
	
	// Iterate through sorted edges
	for (auto it : edges){
		int cost = it.first;
		int u = it.second.first;
		int v = it.second.second;
		
		int setU = ds.find(u);
		int setV = ds.find(v);
		
		// If including this edge doesn't form a cycle
		if (setU != setV){
			// Add edge to MST
			selectedEdgesK.push_back({ u, v });
			costMSTKruskal += cost;
			
			// Merge the two sets
			ds.merge(setU, setV);
		}
	}
}

void Graph::printEdgesK(){
	cout << "Selected Edges Kruskal: ";
	for (auto it:selectedEdgesK){
		cout << "(" << it.first << ", " << it.second << ") ";
	}
	cout << endl;
}

int main(){
	int V, E;
	cin >> V >> E;
	Graph g(V, E);
	g.load();
	// g.print();
	g.primMST();
	cout << "Costo total de MST por Prim es: " << g.costMSTPrim << endl;
	g.printEdgesP();
	g.kruskalMST();
	cout << "Costo total de MST por Kruskal es: " << g.costMSTKruskal << endl;
	g.printEdgesK();
	return 0;
}



/* Unidrected Graph
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/
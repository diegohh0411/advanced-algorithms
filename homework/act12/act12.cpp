// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct Point {
    double x, y;
    
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

struct Edge {
    int u, v;
    double weight;
    
    Edge(int u, int v, double weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
    
    bool operator<(const Edge& other) const {
        return this->weight < other.weight;
    }
};

// Union-Find structure
class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    
public:
    // Complejidad: O(n)
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find with path compression
    // Complejidad: O(α(n)) donde α es la inversa de Ackermann
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Union by rank
    // Complejidad: O(α(n)) donde α es la inversa de Ackermann
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false;
        }
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        return true;
    }
};

// Complejidad: O(1)
double euclideanDistance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Kruskal
// Complejidad: O(E log E)
double kruskal(std::vector<Point>& points) {
    int n = points.size();
    std::vector<Edge> edges;
    
    // Build edges between all pairs
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = euclideanDistance(points[i], points[j]);
            edges.push_back(Edge(i, j, dist));
        }
    }
    
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    double totalCost = 0.0;
    int edgesAdded = 0;
    
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            totalCost += edge.weight;
            edgesAdded++;
            
            if (edgesAdded == n - 1) {
                break;
            }
        }
    }
    
    return totalCost;
}

// Complejidad: O(n)
std::vector<Point> readInput() {
    int n;
    std::cin >> n;
    
    std::vector<Point> points;
    
    for (int i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        points.push_back(Point(x, y));
    }
    
    return points;
}

// Complejidad: O(n^2 log n)
int main() {
    std::vector<Point> points = readInput();
    
    double result = kruskal(points); // O(n^2 log n)
    
    std::cout << std::fixed << std::setprecision(2) << result << std::endl;
    
    return 0;
}
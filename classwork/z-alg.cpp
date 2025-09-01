// Diego Hernández Herrera, A01198786

#include <iostream>
#include <vector>

std::vector<int> z_function(std::string p, std::string t) {
    std::string text = p + "$" + t;

    int n = text.size();

    std::vector<int> z(n, 0);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) {
            z[i] = std::min(r - i, z[i - l]);
        }
        while (i + z[i] < n && text[z[i]] == text[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

int main() {
    std::string p, t;
    std::cin >> p >> t;

    std::vector<int> zF = z_function(p, t);

    bool entre = true;
    
    for (int i = 0; i < zF.size(); i++) {
        if (zF[i] == p.size()) {
            std::cout << zF[i] - p.size() << " ";
            entre = true;
        }
    }

    if (!entre) {
        std::cout << "No hubo coincidencias" << std::endl;
    }
}
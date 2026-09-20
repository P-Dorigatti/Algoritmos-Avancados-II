#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point { int x, y; };

int calcular_distancia(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int n;
vector<Point> pontos;

map<pair<vector<bool>, int>, int> memo;

int tsp(vector<bool>& visitados, int u) {
    bool todos_visitados = true;
    for (int i = 1; i <= n; ++i) {
        if (!visitados[i]) {
            todos_visitados = false;
            break;
        }
    }

    if (todos_visitados) {
        return calcular_distancia(pontos[u], pontos[0]);
    }
    
    if (memo.count({visitados, u})) {
        return memo[{visitados, u}];
    }

    int menor_custo = 1e9;

    for (int v = 1; v <= n; ++v) {
        if (!visitados[v]) {
            
            visitados[v] = true;
            
            int custo_caminho = calcular_distancia(pontos[u], pontos[v]) + tsp(visitados, v);
            menor_custo = min(menor_custo, custo_caminho);
            
            visitados[v] = false; 
        }
    }

    return memo[{visitados, u}] = menor_custo;
}

void solve() {
    int largura, altura;
    cin >> largura >> altura;

    pontos.clear();
    memo.clear();
    
    Point p;
    cin >> p.x >> p.y;
    pontos.push_back(p);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p.x >> p.y;
        pontos.push_back(p); 
    }

    if (n == 0) {
        cout << 0 << "\n";
        return;
    }

    vector<bool> visitados(n + 1, false);
    
    int menor_rota = tsp(visitados, 0);
    printf("A menor rota tem tamanho %d.\n", menor_rota);
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}
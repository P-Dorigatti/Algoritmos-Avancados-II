#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pontos;

vector<vector<int>> memo;

int calcula_custo(int esq, int dir) {
    if (esq + 1 == dir) {
        return 0;
    }

    if (memo[esq][dir] != -1) {
        return memo[esq][dir];
    }

    int menor_custo = 1e9;

    for (int i = esq + 1; i < dir; ++i) {
        int custo_atual = (pontos[dir] - pontos[esq]) + 
                          calcula_custo(esq, i) + 
                          calcula_custo(i, dir);
                          
        menor_custo = min(menor_custo, custo_atual);
    }

    return memo[esq][dir] = menor_custo;
}

void solve() {
    int l;
    int n;
    cin >> l;
    cin >> n; 

    pontos.clear();
    pontos.push_back(0); 

    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        pontos.push_back(c); 
    }
    
    pontos.push_back(l);

    int total_pontos = n + 2;

    memo.assign(total_pontos, vector<int>(total_pontos, -1));

    int resultado = calcula_custo(0, total_pontos - 1);

    cout << "O custo mínimo de quebra é " << resultado << ".\n";
}

int main() {

    int num_casos;
    if (cin >> num_casos) {
        while (num_casos--) {
            solve();
        }
    }
    return 0;
}
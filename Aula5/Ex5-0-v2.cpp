#include <iostream>
#include <vector>

using namespace std;

bool verifica_viabilidade(long long max_por_estante, const vector<long long>& instrumentos, long long p) {
    long long estantes_necessarias = 0;
    
    for (long long quantidade : instrumentos) {
        estantes_necessarias += (quantidade + max_por_estante - 1) / max_por_estante;
        
        if (estantes_necessarias > p) {
            return false;
        }
    }
    
    return true;
}

void resolver_caso() {
    long long p, n;
    cin >> p >> n;

    vector<long long> instrumentos(n);
    long long max_musicos_grupo = 0;
    
    for (int i = 0; i < n; ++i) {
        cin >> instrumentos[i];
        if (instrumentos[i] > max_musicos_grupo) {
            max_musicos_grupo = instrumentos[i];
        }
    }

    long long esquerda = 1; 
    long long direita = max_musicos_grupo;
    long long resposta = max_musicos_grupo;

    while (esquerda <= direita) {
        long long meio = esquerda + (direita - esquerda) / 2;

        if (verifica_viabilidade(meio, instrumentos, p)) {
            resposta = meio;
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }

    cout << resposta << "\n";
}

int main() {
    
    int casos_teste;
    if (cin >> casos_teste) {
        while (casos_teste--) {
            resolver_caso();
        }
    }
    return 0;
}
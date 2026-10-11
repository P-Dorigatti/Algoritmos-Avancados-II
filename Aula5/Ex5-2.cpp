#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void resolver_caso() {
    int N, F;
    cin >> N >> F;

    vector<int> pai(N + 1, 0);
    vector<long long> custo_subida(N + 1, 0);
    vector<vector<pair<int, long long>>> adj(N + 1);

    for (int i = 0; i < N - 1; ++i) {
        int A, B;
        long long C;
        cin >> A >> B >> C;
        pai[B] = A;
        custo_subida[B] = C;
        adj[A].push_back({B, C});
    }

    vector<int> amigos(F);
    for (int i = 0; i < F; ++i) {
        cin >> amigos[i];
    }

    long long custo_total_subarvore = 0;
    vector<bool> visitado(N + 1, false);
    visitado[1] = true;

    for (int amigo : amigos) {
        int atual = amigo;
        while (!visitado[atual]) {
            visitado[atual] = true;
            custo_total_subarvore += custo_subida[atual];
            atual = pai[atual];
        }
    }

    vector<long long> energia_ate_topo(N + 1, 0);
    queue<int> fila;
    fila.push(1);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (auto& aresta : adj[u]) {
            int vizinho = aresta.first;
            long long custo = aresta.second;
            energia_ate_topo[vizinho] = energia_ate_topo[u] + custo;
            fila.push(vizinho);
        }
    }

    long long maior_economia = 0;
    for (int amigo : amigos) {
        maior_economia = max(maior_economia, energia_ate_topo[amigo]);
    }

    long long resposta = custo_total_subarvore - maior_economia;
    cout << resposta << "\n";
}

int main() {
    int T;
    if (cin >> T) {
        while (T--) {
            resolver_caso();
        }
    }
    return 0;
}
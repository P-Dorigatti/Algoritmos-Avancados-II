#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int M, N;
vector<string> mapa;
vector<vector<bool>> visitado;
char terra;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int explorarContinente(int x, int y) {
    visitado[x][y] = true;
    int tamanho = 1;

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        
        int ny = (y + dy[i] + N) % N;

        if (nx >= 0 && nx < M) {
            if (mapa[nx][ny] == terra && !visitado[nx][ny]) {
                tamanho += explorarContinente(nx, ny);
            }
        }
    }

    return tamanho;
}

void solve() {
    if (!(cin >> M >> N)) return;

    mapa.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> mapa[i];
    }

    int X, Y;
    cin >> X >> Y;

    visitado.assign(M, vector<bool>(N, false));

    terra = mapa[X][Y];

    explorarContinente(X, Y);

    int maior_continente = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mapa[i][j] == terra && !visitado[i][j]) {
                int tamanho_atual = explorarContinente(i, j);
                maior_continente = max(maior_continente, tamanho_atual);
            }
        }
    }

    cout << maior_continente << "\n";
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
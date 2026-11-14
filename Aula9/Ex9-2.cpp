#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;

    // pos[x] guarda o índice (0 a n-1) em que a pedra x aparece na primeira sequência
    vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        int stone;
        cin >> stone;
        pos[stone] = i;
    }

    // Vetor auxiliar para calcular o tamanho da LIS em O(N log N)
    vector<int> tails;
    tails.reserve(n);

    // Lê a segunda sequência, converte cada pedra para seu índice na primeira e atualiza a LIS
    for (int i = 0; i < n; ++i) {
        int stone;
        cin >> stone;
        int idx = pos[stone];

        auto it = lower_bound(tails.begin(), tails.end(), idx);
        if (it == tails.end()) {
            tails.push_back(idx);
        } else {
            *it = idx;
        }
    }

    int lcs_length = static_cast<int>(tails.size());
    cout << 2 * (n - lcs_length) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }

    return 0;
}
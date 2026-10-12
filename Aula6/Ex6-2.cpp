#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t, n;

    cin >> t >> n;

    vector<int> d(n), v(n), custo(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i] >> v[i];
        custo[i] = 3 * d[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(t + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= t; ++j) {
            if (custo[i - 1] <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - custo[i - 1]] + v[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int energia_restante = t;
    vector<int> escolhidos;

    for (int i = n; i > 0; --i) {
        if (dp[i][energia_restante] != dp[i - 1][energia_restante]) {
            escolhidos.push_back(i - 1);
            energia_restante -= custo[i - 1];
        }
    }

    reverse(escolhidos.begin(), escolhidos.end());

    cout << dp[n][t] << "\n";
    cout << escolhidos.size() << "\n";
    
    for (int idx : escolhidos) {
        cout << d[idx] << " " << v[idx] << "\n";
    }

    return 0;
}
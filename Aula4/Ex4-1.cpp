#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e6;

// C(N, K) = N!/((N - K)! * K!)
int bin(int N, int K) {
    if(K > N || K < 0) return 0;
    K = min(N, N - K); // C(N, K) == C(N, N-K)
    vector<int> dp(K + 1, 0);
    dp[0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = min(i, K); j > 0; j--) {
            dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }

    return dp[K];
}

int possibilities(int N, int K) {
    return bin(N + K - 1, K - 1);
}

void problem() {
    int N;
    int K;
    cin >> N;
    cin >> K;
    cout << possibilities(N, K) << endl;
}

int main() {
    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        problem();
    }

    return 0;
}
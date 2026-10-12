#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int> dp(n+1, n);
    dp[0] = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j*j <= i; j++){
            dp[i] = min(dp[i], dp[i-j*j] + 1);
        }
    }

    cout << dp[n] << endl;
}

int main(){
    int t;
    if(cin >> t){
        while (t--){
            solve();
        }
    }

    return 0;
}
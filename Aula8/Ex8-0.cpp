#include <iostream>
#include <cmath>

using namespace std;

void solve() {
    unsigned long long n;
    cin >> n;
    
    unsigned long long raiz = round(sqrt(n));
    
    if (raiz * raiz == n) {
        cout << "ativada\n";
    } else {
        cout << "desativada\n";
    }
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
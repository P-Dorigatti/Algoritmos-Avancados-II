#include <iostream>
#include <string>

using namespace std;

int soma_digitos(int n) {
    int s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

void solve() {
    string n;
    cin >> n;
    
    int soma = 0;
    for (char c : n) {
        soma += (c - '0');
    }
    
    if (soma % 9 != 0 || soma == 0) {
        cout << 0 << "\n";
        return;
    }

    int grau = 1;
    
    while (soma > 9) {
        soma = soma_digitos(soma);
        grau++;
    }
    
    cout << grau << "\n";
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
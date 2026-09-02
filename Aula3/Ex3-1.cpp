#include <iostream>

using namespace std;

const long long MOD = 1000000007;

long long power_modulo(long long a, long long b) {
    long long resultado = 1;
    
    a = a % MOD; 

    while (b > 0) {
        if (b % 2 == 1) {
            resultado = (resultado * a) % MOD;
        }
        
        a = (a * a) % MOD;
        b = b / 2;
    }
    
    return resultado;
}

int main() {

    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        long long a, b;
        cin >> a >> b;
        cout << power_modulo(a, b) << "\n";
    }

    return 0;
}
#include <iostream>

using namespace std;


long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

long long floor_div(long long a, long long b) {
    long long res = a / b;
    long long rem = a % b;
    if (rem < 0) {
        res--;
    }
    return res;
}

long long ceil_div(long long a, long long b) {
    long long res = a / b;
    long long rem = a % b;
    if (rem > 0) {
        res++;
    }
    return res;
}

void solve() {
    long long N, c1, n1, c2, n2;
    cin >> N >> c1 >> n1 >> c2 >> n2;

    long long x0, y0;
    long long g = ext_gcd(n1, n2, x0, y0);

    if (N % g != 0) {
        cout << "sem solucao\n";
        return;
    }

    long long fator = N / g;
    long long m1_p = (long long)x0 * fator;
    long long m2_p = (long long)y0 * fator;

    long long passo1 = n2 / g;
    long long passo2 = n1 / g;

    long long k_min = ceil_div(-m1_p, passo1);
    long long k_max = floor_div(m2_p, passo2);

    if (k_min > k_max) {
        cout << "sem solucao\n";
        return;
    }

    long long custo_relativo = (long long)c1 * n2 - (long long)c2 * n1;
    
    long long k_otimo;
    if (custo_relativo >= 0) {
        k_otimo = k_min;
    } else {
        k_otimo = k_max;
    }

    long long m1_final = (long long)(m1_p + k_otimo * passo1);
    long long m2_final = (long long)(m2_p - k_otimo * passo2);

    cout << m1_final << " " << m2_final << "\n";
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
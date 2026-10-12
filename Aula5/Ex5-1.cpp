#include <iostream>
#include <vector>

using namespace std;

void solve() {
    long long n, m, a, c, x0;
    cin >> n >> m >> a >> c >> x0;

    vector<long long> arr(n);
    long long atual = x0;
    
    for (int i = 0; i < n; i++) {
        atual = (a * atual + c) % m;
        arr[i] = atual;
    }

    int elementos_encontrados = 0;
    
    for (int i = 0; i < n; i++) {
        long long alvo = arr[i];
        int low = 0;
        int high = n - 1;
        bool achou = false;
        
        while (low <= high) {
            int mid = low + (high - low) / 2; 
            
            if (arr[mid] == alvo) {
                achou = true;
                break;
            } 
            else if (alvo < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        if (achou) {
            elementos_encontrados++;
        }
    }

    cout << elementos_encontrados << "\n";
}

int main() {
    int casos_teste;
    if (cin >> casos_teste) {
        while (casos_teste--) {
            solve();
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int m, w;
        cin >> m;
        cin >> w;

        vector<int> pesos;
    
        for(int j = 0; j < m; j++){
            int peso;
            cin >> peso;
            pesos.push_back(peso);

        }

        sort(pesos.begin(), pesos.end());
        
        int soma = 0;
        int contador = 0;
        for(int j = 0; j < m; j++){
            if(soma + pesos[j] > w){
                break;
            }
            else{
                soma += pesos[j];
                contador += 1;
            }

        }

        cout << contador << endl;
        
    }
}
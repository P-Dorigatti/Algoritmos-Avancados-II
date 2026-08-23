#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void preenche_quadro(vector<vector<char>>& matriz, int tam){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(matriz[i][j] != '.') continue;

            for(int k = 65; k < 70; k++){
                if(i-1 >= 0 && matriz[i-1][j] == k) continue;
                if(j-1 >= 0 && matriz[i][j-1] == k) continue;
                if(i+1 < tam && matriz[i+1][j] == k) continue;
                if(j+1 < tam && matriz[i][j+1] == k) continue;

                matriz[i][j] = k;
                break;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int tam;
        cin >> tam;
        vector<vector<char>> matriz(tam, vector<char>(tam));

        for(int j = 0; j < tam; j++){
            for(int k = 0; k < tam; k++){
                cin >> matriz[j][k];
            }
        }

        preenche_quadro(matriz, tam);

        cout << "Caso " << i+1 << ":" << endl;
        for(int j = 0; j < tam; j++){
            for(int k = 0; k < tam; k++){
                cout << matriz[j][k];
            }
            cout << endl;
        }
        
    }
}
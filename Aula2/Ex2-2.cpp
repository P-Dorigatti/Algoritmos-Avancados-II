#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int casos_teste;
    int N; // nro de palavras
    int L; // nro de linhas por pag
    int C; // nro de caracteres por linha

    cin >> casos_teste;

    for(int i = 0; i < casos_teste; i++){
        cin >> N;
        cin >> L;
        cin >> C;

        vector<int> tam_palavras(N);
        for(int j = 0; j < N; j++){
            string palavra;
            cin >> palavra;
            tam_palavras[j] = palavra.length();
        }

        int contador_linha = 1;

        int soma_caracter = 0;
        for(int j = 0; j < N; j++){
            if(soma_caracter + tam_palavras[j] > C){
                contador_linha++;
                soma_caracter = tam_palavras[j] + 1;
            }
            else{
                soma_caracter += tam_palavras[j] + 1;
            }
        }
        int contador_pagina = (contador_linha + L - 1)/L;
        cout << contador_pagina << endl;
    }
}